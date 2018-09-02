# Contributing to TopDown
The following is a set of guidelines to follow when contributing to TopDown.

## Style guides
The following is a set of guidelines to follow to maintain a consistent codebase.

### Naming
* PascalCase for type names
* ALL_CAPS for constants
* snake_case for everything else

### Headers
* Experimental: Use forward declarations only where needed (e.g. cyclic dependencies)  
     This is a tiny project, and the modules may fix the issue in the future, if it arises

### Conditionals
* Don't use implicit boolean tests (e.g. compare to `nullptr` or `0` explicitly)

### Classes
* Experimental: Prefer get/set/get/set order for properties, instead of get/get/set/set
* Prefer instance methods to static methods - not developing a library here, a small amount of coupling is allowed

### Functions/Methods
* Experimental: Prefer left (west) const  
     Despite the rules being simpler for east const, west const is more natural in many cases, and the cases, where the rules are hard - are rare