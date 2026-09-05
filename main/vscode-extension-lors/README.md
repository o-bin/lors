# Lors VS Code Extension

This is a local, unpublished VS Code extension to provide syntax highlighting and a custom pastel color theme for the "Lors" programming language.

## Language Support

This extension adds syntax highlighting and basic support for `.lr` files, including:
- Variables (`datum`)
- Data Types (`whole`, `precise`, `series`, `state`)
- Conditionals (`verify`, `then`, `otherwise`, `conclude`)
- Loops (`cycle`, `do`, `conclude`)
- Functions (`algorithm`, `begin`, `result`)
- Built-ins (`reveal`)
- Standard language constructs (comments, strings, numbers, booleans, operators, and variables)

## Theme

The extension also includes the **Lors Pastel Theme** which highlights syntax elements using a soft, aesthetic pastel color palette against a dark editor background.

## Installation Instructions (Local Linux)

Follow these steps to load this extension locally into your VS Code instance on Linux:

1. Copy or move this entire directory (`vscode-extension-lors`) into your VS Code extensions folder:
   ```bash
   cp -r vscode-extension-lors ~/.vscode/extensions/
   ```

2. Reload VS Code:
   - Open VS Code.
   - Press `Ctrl+Shift+P` to open the Command Palette.
   - Type `Reload Window` and hit Enter.

3. Activate the Theme:
   - Press `Ctrl+K` then `Ctrl+T` to open the Color Theme picker.
   - Select **Lors Pastel Theme** from the list.

4. Test it out:
   - Open any file with the `.lr` extension (or create a new one).
   - Ensure the language mode in the bottom right corner of VS Code says "Lors".
   - Start typing Lors code and enjoy the syntax highlighting!
