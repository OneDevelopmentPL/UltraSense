
# Contributing to UltraSense

Thanks for your interest in contributing! UltraSense is a small, focused library - contributions that keep it **lightweight and easy to use** are most welcome.

---

## Ways to Contribute

- 🐛 Report bugs
- 💡 Suggest new features or improvements
- 📖 Improve documentation or examples
- 🔧 Submit a pull request with a fix or new feature

---

## Reporting Bugs

Before opening an issue, please check if it has already been reported.

When filing a bug, include:
- Arduino board and version (e.g. Arduino Uno, IDE 2.3)
- Library version
- A minimal code snippet that reproduces the problem
- What you expected vs. what actually happened

---

## Suggesting Features

Open an issue with the label `enhancement` and describe:
- What problem it solves
- How you'd expect the API to look
- Any edge cases to consider

---

## Submitting a Pull Request

1. Fork the repository
2. Create a branch with a descriptive name:
   ```
   git checkout -b fix/out-of-range-edge-case
   git checkout -b feature/temperature-compensation
   ```
3. Make your changes
4. Test on real hardware if possible (HC-SR04 + Arduino)
5. Open a pull request against `main` with a short description of what changed and why

---

## Code Style

- Keep the code readable and minimal — this library targets beginners too
- Use `camelCase` for methods and variables, `UPPER_SNAKE_CASE` for constants
- Add a short comment above any non-obvious logic
- Don't introduce external dependencies

---

## Adding Examples

If you're adding a new example sketch, place it in the `examples/` folder and name it with a number prefix, e.g. `05_MyFeature`. Make sure it compiles cleanly and includes comments explaining what it do.

---

## License

By contributing, you agree that your changes will be released under the [O-LA 1.1](LICENSE) that covers this project.
