# Contributing Guidelines

## Code Style

- **Indentation**: 4 spaces
- **Naming Conventions**:
  - Classes: `PascalCase` (e.g., `Matrix`, `Vector`)
  - Functions/Methods: `camelCase` (e.g., `getElement()`, `transpose()`)
  - Member variables: `snake_case` with `_` prefix (e.g., `_data`, `_shape`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_SIZE`)
  
- **Comments**: Use C++ style comments (`//`) for single lines and `/** */` for documentation

## Documentation

- Use Doxygen style comments for classes and public methods
- Document parameters, return values, and exceptions
- Include usage examples for complex functionality

## Testing

- Add tests for new features in the appropriate module
- Run benchmarks to ensure no performance regressions
- Use the `benchmark()` function in `Utils/include/Utils/benchmark.h` for performance comparisons

## Commit Messages

- Use clear, descriptive messages
- Prefix with the component affected (e.g., `[LinAlg]`, `[NN Framework]`)
- Example: `[LinAlg Optimize transpose with cache-friendly block algorithm`

## Pull Request Process

1. Update README.md with any new features or API changes
2. Ensure code follows style guidelines
3. Add appropriate documentation
4. Test thoroughly before submitting

## Reporting Issues

When reporting issues, please include:
- Clear description of the problem
- Steps to reproduce
- Expected vs. actual behavior
- System information (OS, compiler version, etc.)
