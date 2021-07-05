# Examples

There is a list of examples for SA:MP Vectors.

## Vector_Create

If you use `Vector_Create()` when you create the vector variable, you will get an error. So, you need to use `Vector_Create()` at `OnGameModeInit()`.

```pawn
new Vector:vector1;

public OnGameModeInit()
{
    vector1 = Vector_Create();
    return 1;
}
```

## foreachVector

It's like `foreach` but for vectors.

```pawn
foreachVector(vector1, i) {
    printf("%d", i);
}
```

## Vector_Size

Returns the size of the Vector.

```pawn
new size = Vector_Size(vector1);
```

## Vector_Even

Checks if the size of the vector is even.

```pawn
new size = Vector_Even(vector1);
```

## Vector_Odd

Checks if the size of the vector is odd.

```pawn
new size = Vector_Odd(vector1);
```

## Vector_Empty

Checks if the vector is empty.

```pawn
new size = Vector_Empty(vector1);
```

## Vector_Random

Returns a random element from the vector. If the vector's size is below 1, it returns -1

```pawn
new size = Vector_Random(vector1);
```

## Vector_Begin

Returns the first element from the vector minus one unit.

```pawn
new value = Vector_Begin(vector1);
```

## Vector_End

Returns the last element from the vector plus one unit.

```pawn
new value = Vector_End(vector1);
```

## Vector_First

Returns the first element from the vector.

```pawn
new value = Vector_First(vector1);
```

## Vector_End

Returns the last element from the vector.

```pawn
new value = Vector_End(vector1);
```

## Vector_Next

Finds the next element from vector of the given number. It returns -1 if it doesn't find any value.

```pawn
new value = Vector_Next(vector1, 1);
```

## Vector_Prev

Finds the previous element from vector of the given number. It returns -1 if it doesn't find any value.

```pawn
new value = Vector_Prev(vector1, 1);
```

## Vector_PopBack

It removes the last element from the vector and return it's value.

```pawn
new value = Vector_PopBack(vector1);
```

## Vector_PopFront

It removes the first element from the vector and return it's value.

```pawn
new value = Vector_PopFront(vector1);
```

## Vector_FindIndex

It finds the index from the vector of a value. It returns -1 if the value isn't found in the vector.

```pawn
new index = Vector_FindIndex(vector1, 512);
```

## Vector_FindValue

It finds the value from a specific index of a vector. It returns -1 if the index doesn't exists.

```pawn
new index = Vector_FindValue(vector1, 0);
```

## Vector_Add

It adds the given value to a vector. (**WARNING** If the element already exists, it returns 0)

```pawn
new success = Vector_Add(vector1, 0);
```

## Vector_Remove

It removes the given value from a vector. (**WARNING** If the element doesn't exists, it returns 0)

```pawn
new success = Vector_Remove(vector1, 0);
```

## Vector_Delete

It deletes the element from a specific index. (**WARNING** If the index isn't valid, it returns -1)

```pawn
new success = Vector_Delete(vector1, 0);
```

## Vector_Replace

It replaces the given value to the new value. (**WARNING** If the old value isn't valid, it returns -1)

```pawn
new success = Vector_Replace(vector1, 0, 125);
```

## Vector_ReplaceIndex

It replaces the given value to the specific index. (**WARNING** If the index isn't valid, it returns -1)

```pawn
new success = Vector_ReplaceIndex(vector1, 0, 125);
```

## Vector_Clear

It clears the vector.

```pawn
new success = Vector_Clear(vector1);
```

## External Links

[Quick-Start](https://github.com/skuzzis/vectors/blob/master/pages/quick_start.md) - Quick-Start for SA:MP Vectors.

[Functions List](https://github.com/skuzzis/vectors/blob/master/pages/natives_list.md) - A list of functions for SA:MP Vectors.
