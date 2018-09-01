# Contributing to TopDown
The following is a set of guidelines to follow when contributing to TopDown.

## Style guides
The following is a set of guidelines to follow to maintain a consistent codebase.

### Naming
* CamelCase for type names
* ALL_CAPS for constants
* snake_case for everything else

### Headers
* Experimental: Use forward declarations only where needed (e.g. cyclic dependencies)  
     This is a tiny project, and the modules may fix the issue in the future, if it arises

### Classes
* Experimental: Prefer get/set/get/set order for properties, instead of get/get/set/set

### Functions/Methods
* Experimental: Prefer left (west) const  
     Despite the rules being simpler for east const, west const is more natural in many cases, and the cases, where the rules are hard - are rare