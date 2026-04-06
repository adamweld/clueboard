# clueboard

Personal QMK config for my **Clueboard 66% rev4** (STM32F303cc / Proton C).

The repo ships **two firmware variants**:

| Variant     | File                                  | Source                          | Use on            |
| ----------- | ------------------------------------- | ------------------------------- | ----------------- |
| **Generic** | `clueboard_66_rev4_adamweld_v1.bin`   | `adamweld_v1.json`              | Windows / Linux   |
| **Apple**   | `clueboard_66_rev4_adamweld_apple.bin` | `keymaps/adamweld_apple/`      | macOS             |

The Apple variant adds a working **Globe key** in the second-from-left bottom
row position, so macOS treats it as the real `fn` / Globe key for input source
switching, dictation, the emoji picker, etc. The generic variant has a plain
`LGUI` (Win/Super) in that slot.

## Layouts

### Generic (Windows/Linux) bottom row

```
LCTL · LGUI · LALT · SPACE · LALT · Fn · LCTL
```

### Apple bottom row

```
LCTL · 🌐 · LGUI · SPACE · LALT · Fn · LCTL
```

- 🌐 sends consumer usage `0x029D` (`AC Keyboard Layout Select`), which macOS
  recognises as the Globe key.
- `Fn` (`MO(1)`) is the function-layer toggle right of the spacebar.
- Caps Lock physical position is `LGUI` on the base layer.

Both variants share the same three layers:

| Layer | Purpose                                                   |
| ----- | --------------------------------------------------------- |
| 0     | Base — typing (+ Globe on the Apple variant)              |
| 1     | Fn — F-row, media controls, arrows on `Home`/`PgDn`/`End` |
| 2     | RGB underglow + `QK_BOOT` (Fn + Caps Lock + R)            |

## Files

```
adamweld_v1.json                       Generic config — QMK Configurator JSON
adamweld_v2_apple.json                 Apple config — QMK Configurator JSON (reference; uses ANY(AP_GLOB))
clueboard_66_rev4_adamweld_v1.bin      Generic prebuilt firmware (Win/Linux)
clueboard_66_rev4_adamweld_apple.bin   Apple prebuilt firmware (macOS)
keymaps/adamweld_apple/keymap.c        Apple variant source — defines AP_GLOB and process_record_user
keymaps/adamweld_apple/rules.mk        KEYBOARD_SHARED_EP = yes (lets Globe combo with modifiers)
```

The Apple configurator JSON (`adamweld_v2_apple.json`) can't actually compile —
Globe is a custom keycode and the Configurator wraps it as `ANY(AP_GLOB)`. It's
kept for layer-layout reference only — **`keymaps/adamweld_apple/keymap.c` is
what gets built**. The generic JSON, by contrast, uses only stock QMK keycodes
and *can* be built directly via the QMK Configurator if you ever need to.

## Flashing a prebuilt binary

You don't need a QMK build environment for this — just `dfu-util`:

```sh
brew install dfu-util            # one-time
```

Then enter bootloader and flash:

1. **Plug the keyboard directly into your computer.** Not through a KVM — KVMs
   only pass HID, so the DFU device won't be visible.
2. Enter DFU mode: hold the **FLASH** button on the underside of the PCB while
   plugging in USB, then release. (FLASH is wired to BOOT0, not RESET — a plain
   reset won't work.)
3. Confirm the bootloader is up:
   ```sh
   dfu-util -l
   # should show: Found DFU: [0483:df11] ... STM32 BOOTLOADER
   ```
4. Flash the variant you want:
   ```sh
   # Apple (macOS)
   dfu-util -a 0 -d 0483:DF11 -s 0x08000000:leave -D clueboard_66_rev4_adamweld_apple.bin

   # Generic (Windows/Linux)
   dfu-util -a 0 -d 0483:DF11 -s 0x08000000:leave -D clueboard_66_rev4_adamweld_v1.bin
   ```

The board reboots back into normal mode after flashing. On macOS, verify the
Globe key in **System Settings → Keyboard**.

## Building the Apple variant from source

You only need this if you change `keymaps/adamweld_apple/keymap.c`.

### One-time setup

```sh
brew install qmk/qmk/qmk
qmk setup -y                       # clones ~/qmk_firmware
```

**Toolchain gotcha:** Homebrew's `arm-none-eabi-gcc` (15.x) ships without
newlib and fails QMK builds with `stdint.h: No such file or directory`. Use the
official ARM tarball instead:

```sh
mkdir -p ~/toolchains && cd ~/toolchains
curl -LO https://developer.arm.com/-/media/Files/downloads/gnu/13.3.rel1/binrel/arm-gnu-toolchain-13.3.rel1-darwin-arm64-arm-none-eabi.tar.xz
tar -xf arm-gnu-toolchain-13.3.rel1-darwin-arm64-arm-none-eabi.tar.xz
```

Add to your shell rc (or export per session):

```sh
export PATH="$HOME/toolchains/arm-gnu-toolchain-13.3.rel1-darwin-arm64-arm-none-eabi/bin:$PATH"
```

### Build

Symlink (or copy) this keymap into your QMK tree:

```sh
ln -sf "$PWD/keymaps/adamweld_apple" \
       ~/qmk_firmware/keyboards/clueboard/66/rev4/keymaps/adamweld_apple
```

Then compile:

```sh
cd ~/qmk_firmware
qmk compile -kb clueboard/66/rev4 -km adamweld_apple
```

The output `.bin` lands in `~/qmk_firmware/clueboard_66_rev4_adamweld_apple.bin`.
Copy it back into this repo to update the prebuilt artifact.

## Gotchas, in one place

- **KVMs block DFU.** Always plug direct to the host machine when flashing.
- **FLASH button = BOOT0**, not RESET. Hold it during plug-in to enter
  bootloader. A plain reset on STM32 just restarts firmware; it does *not*
  enter the system bootloader like a Pro Micro would.
- **Globe + modifiers** requires `KEYBOARD_SHARED_EP = yes` (already set in
  `rules.mk`). Without it, Globe works alone but can't combo with Cmd/Ctrl/etc.
