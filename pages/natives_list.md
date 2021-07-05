# Natives list

Below will be an updated list of natives and functions.

```pawn
native Vector:Vector_Create();
native Vector_Size(Vector:vector_name);
native Vector_Even(Vector:vector_name);
native Vector_Odd(Vector:vector_name);
native Vector_Empty(Vector:vector_name);
native Vector_Random(Vector:vector_name);
native Vector_DebugMode(bool:toggle);

native Vector_Begin(Vector:vector_name);
native Vector_End(Vector:vector_name);
native Vector_First(Vector:vector_name);
native Vector_Last(Vector:vector_name);
native Vector_Next(Vector:vector_name, value);
native Vector_Prev(Vector:vector_name, value);
native Vector_PopBack(Vector:vector_name);
native Vector_PopFront(Vector:vector_name);
native Vector_FindIndex(Vector:vector_name, value);
native Vector_FindValue(Vector:vector_name, index);

native Vector_Add(Vector:vector_name, value);
native Vector_Remove(Vector:vector_name, value);
native Vector_Delete(Vector:vector_name, index);
native Vector_Replace(Vector:vector_name, old_value, new_value);
native Vector_ReplaceIndex(Vector:vector_name, index, new_value);
native Vector_Clear(Vector:vector_name);
```

## External links

[Quick-Start](https://github.com/skuzzis/vectors/blob/master/pages/quick_start.md) - Quick-Start for SA:MP Vectors.

[Examples](https://github.com/skuzzis/vectors/blob/master/pages/examples.md) - A list of examples for SA:MP Vectors.
