# Quick-Start

## How I install the plugin?

To get started, you need to download the [Latest Releases](https://github.com/skuzzis/vectors/releases) and put these two folders inside your server.

Next in your gamemode, you need to include the file like this:

```pawn
#include <a_samp>
#include <vectors>
...
```

## How to create a vector?

Firstly you need to declare a variable with tag `Vector:` in your gamemode. and use `Vector_Create()` at `OnGameModeInit()` to create it up.

**WARNING** If you use it when you declare the vector, you will get some errors.

```pawn

new Vector:vector1;

public OnGameModeInit() {
    vector1 = Vector_Create();
    return 1;
}
```

## How do I use the vectors?

You can use the vectors with the list of functions which are [here](https://github.com/skuzzis/vectors/blob/master/pages/natives_list.md).

Also, you can get some examples from [here](https://github.com/skuzzis/vectors/blob/master/pages/examples.md).

## External links

[Functions List](https://github.com/skuzzis/vectors/blob/master/pages/natives_list.md) - A list of functions for Vectors.

[Examples](https://github.com/skuzzis/vectors/blob/master/pages/examples.md) - A list of examples for Vectors.
