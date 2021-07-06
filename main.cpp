/*
	Copyright (c) 2021 Andrei "SkuZZi" Sebastian

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/


#include <cstddef>
#include <unordered_set>
#include <vector>
#include <cassert>

#include "SDK/amx/amx.h"
#include "SDK/plugincommon.h"
#include "pluginconfig.h"
#include "pluginutils.h"


extern void* pAMXFunctions;
void* (*logprintf)(const char* fmt, ...);

bool debugging = false;
unsigned long int vctID = 0;
std::vector<std::unordered_set<int>> vectors;
std::vector<std::vector<int>> copy_vectors;

/// <summary>
/// Creating the vector
/// </summary>
/// <param name="amx"> Vector_Create </param>
/// <param name="params"> none </param>
/// <returns> vectorID </returns>

static cell AMX_NATIVE_CALL n_Vector_Create(AMX* amx, cell* params)
{
	std::unordered_set<int> unordered_setts;
	std::vector<int> copy_unordered_setts;
	vectors.push_back(unordered_setts);
	copy_vectors.push_back(copy_unordered_setts);

	if(debugging) logprintf("%s: A new vector has been created with ID: %d.", pluginutils::GetCurrentNativeFunctionName(amx), vctID + 1);
	return static_cast<cell>(++vctID);
}

/// <summary>
/// Toggles on and off the vector's debug mode.
/// </summary>
/// <param name="amx">Vector_DebugMode</param>
/// <param name="params">boolean toggle</param>
/// <returns>1</returns>
/// 
static cell AMX_NATIVE_CALL n_Vector_DebugMode(AMX* amx, cell* params) {
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;

	if (debugging == static_cast<bool>(params[1]))
		return logprintf("%s: The debugging mode is already %s.", pluginutils::GetCurrentNativeFunctionName(amx), debugging == true ? "enabled" : "disabled"), 1;
	
	debugging = static_cast<bool>(params[1]);
	return logprintf("%s: The debugging mode has been %s.", pluginutils::GetCurrentNativeFunctionName(amx), debugging == true ? "enabled" : "disabled"), 1;
}

/// <summary>
/// Shows the size of the vector elements
/// </summary>
/// <param name="amx"> Vector_Size </param>
/// <param name="params"> vectorID </param>
/// <returns> size of vectorID </returns>

static cell AMX_NATIVE_CALL n_Vector_Size(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;

	auto size = vectors[static_cast<unsigned long int>(params[1]) - 1].size();
	if (debugging) logprintf("%s: Returning the size of vector %d as %d.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<int>(params[1]), size);
	return size;
}

/// <summary>
/// Shows if the vector is odd or not.
/// </summary>
/// <param name="amx"> Vector_Odd </param>
/// <param name="params"> vectorID </param>
/// <returns> true if vector is odd, otherwise false </returns>

static cell AMX_NATIVE_CALL n_Vector_Odd(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;

	auto size = vectors[static_cast<unsigned long int>(params[1]) - 1].size();
	if (debugging) logprintf("%s: The size of vector %d is %d, and the return will be %s.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<int>(params[1]), size, size % 2 == 1 ? "true" : "false");
	return size % 2 == 1;
}

/// <summary>
/// Shows if the vector is even or not.
/// </summary>
/// <param name="amx"> Vector_Even </param>
/// <param name="params"> vectorID </param>
/// <returns> true if vector is even, otherwise false </returns>

static cell AMX_NATIVE_CALL n_Vector_Even(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;

	auto size = vectors[static_cast<unsigned long int>(params[1]) - 1].size();
	if (debugging) logprintf("%s: The size of vector %d is %d, and the return will be %s.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<int>(params[1]), size, size % 2 == 0 ? "true" : "false");
	return size % 2 == 0;
}

/// <summary>
/// Shows if the vector is empty or not.
/// </summary>
/// <param name="amx"> Vector_Empty </param>
/// <param name="params"> vectorID </param>
/// <returns> true if vector is empty, otherwise false </returns>

static cell AMX_NATIVE_CALL n_Vector_Empty(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;

	auto size = vectors[static_cast<unsigned long int>(params[1]) - 1].size();
	if (debugging) logprintf("%s: The size of vector %d is %d, and the return will be %s.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<int>(params[1]), size, size == 0 ? "true" : "false");
	return vectors[static_cast<int>(params[1]) - 1].empty();
}

/// <summary>
/// Adds a element into the vector.
/// </summary>
/// <param name="amx"> Vector_Add </param>
/// <param name="params"> vectorID, value </param>
/// <returns> 1 </returns>

static cell AMX_NATIVE_CALL n_Vector_Add(AMX* amx, cell* params)
{
	unsigned short int num_args = 2;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	
	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	if (debugging) logprintf("%s: Adding element to vector %d, value %d.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<int>(params[1]), static_cast<int>(params[2]));
	vectors[vectorID].insert(static_cast<int>(params[2]));
	copy_vectors[vectorID].push_back(static_cast<int>(params[2]));
	return 1;
}

/// <summary>
/// Clears the elements from the vector.
/// </summary>
/// <param name="amx"> Vector_Clear </param>
/// <param name="params"> vectorID </param>
/// <returns> 1 if vector has elements, otherwise returns 0 </returns>

static cell AMX_NATIVE_CALL n_Vector_Clear(AMX* amx, cell* params) 
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0) {
		if (debugging) logprintf("%s: The vector %d it's already empty.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<unsigned long int>(params[1]) - 1);
		return 0;
	}

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	if (debugging) logprintf("%s: Clearing %d elements from vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), vectors[vectorID].size(), vectorID + 1);
	vectors[vectorID].clear();
	copy_vectors[vectorID].clear();
	return 1;
}

/// <summary>
/// Deletes a specific value from vector.
/// </summary>
/// <param name="amx"> Vector_Remove </param>
/// <param name="params"> vectorID, value </param>
/// <returns> 1 if element has been removed, otherwise returns 0 </returns>

static cell AMX_NATIVE_CALL n_Vector_Remove(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].find(static_cast<int>(params[2])) == vectors[static_cast<unsigned long int>(params[1]) - 1].end())
		return 0;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	int value = static_cast<int>(params[2]);
	if (debugging) logprintf("%s: Removed element %d from vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), value, vectorID + 1);
	vectors[vectorID].erase(value);
	copy_vectors[vectorID].erase(std::lower_bound(copy_vectors[vectorID].begin(), copy_vectors[vectorID].end(), value));
	return 1;
}

/// <summary>
/// Deletes a specific value from vector.
/// </summary>
/// <param name="amx"> Vector_Remove </param>
/// <param name="params"> vectorID, value </param>
/// <returns> 1 if element has been removed, otherwise returns 0 </returns>

static cell AMX_NATIVE_CALL n_Vector_Delete(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (static_cast<int>(params[2]) < 0 || static_cast<unsigned int>(params[2]) >= vectors[static_cast<unsigned long int>(params[1]) - 1].size())
		return 0;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	int value = static_cast<int>(params[2]);
	if (debugging) logprintf("%s: Removed element at index %d from vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), value, vectorID + 1);
	vectors[vectorID].erase(vectors[static_cast<unsigned long int>(params[1]) - 1].find(value));
	copy_vectors[vectorID].erase(copy_vectors[vectorID].begin() + value);
	return 1;
}

/// <summary>
/// Returns the first element from vector minus one unit.
/// </summary>
/// <param name="amx"> Vector_Begin </param>
/// <param name="params"> vectorID </param>
/// <returns> Returns the first element from vector minus one unit. </returns>

static cell AMX_NATIVE_CALL n_Vector_Begin(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return 0;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	auto it = copy_vectors[vectorID][0] - 1;
	if (debugging) logprintf("%s: Returning the value %d for vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), it, vectorID + 1);
	return it;
}

/// <summary>
/// Returns the last element from vector plus one unit.
/// </summary>
/// <param name="amx"> Vector_End </param>
/// <param name="params"> vectorID </param>
/// <returns> Returns the last element from vector plus one unit. </returns>

static cell AMX_NATIVE_CALL n_Vector_End(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return 0;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	if (debugging) logprintf("%s: Returning the value %d for vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), copy_vectors[vectorID][copy_vectors[vectorID].size() - 1] + 1, vectorID + 1);
	return copy_vectors[vectorID][copy_vectors[vectorID].size() - 1] + 1;
}

/// <summary>
/// Returns the first element from vector.
/// </summary>
/// <param name="amx"> Vector_First </param>
/// <param name="params"> vectorID </param>
/// <returns> Returns the first element from vector. </returns>

static cell AMX_NATIVE_CALL n_Vector_First(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return 0;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	auto it = copy_vectors[vectorID][0];
	if (debugging) logprintf("%s: Returning the value %d for vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), it, vectorID + 1);
	return it;
}

/// <summary>
/// Returns the last element from vector.
/// </summary>
/// <param name="amx"> Vector_Last </param>
/// <param name="params"> vectorID </param>
/// <returns> Returns the last element from vector. </returns>

static cell AMX_NATIVE_CALL n_Vector_Last(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return 0;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	auto it = copy_vectors[vectorID][copy_vectors[vectorID].size() - 1];
	if (debugging) logprintf("%s: Returning the value %d for vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), it, vectorID + 1);
	return it;
}

/// <summary>
/// Returns the next element for the given value.
/// </summary>
/// <param name="amx"> Vector_Next </param>
/// <param name="params"> vectorID, value </param>
/// <returns> Returns the next element for the given value. If doesn't exists a next one, it returns -1 </returns>

static cell AMX_NATIVE_CALL n_Vector_Next(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() < 2 || vectors[static_cast<unsigned long int>(params[1]) - 1].count(static_cast<int>(params[2])) == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	//auto it = std::next(vectors[vectorID].find(static_cast<int>(params[2])));
	auto it = vectors[vectorID].find(static_cast<int>(params[2]));
	std::advance(it, 1);
	if (debugging) logprintf("%s: Returning the value %d for vector %d, given value %d.", pluginutils::GetCurrentNativeFunctionName(amx), *it, vectorID + 1, static_cast<int>(params[2]));
	return *it;
}

/// <summary>
/// Returns the prev element for the given value.
/// </summary>
/// <param name="amx"> Vector_Prev </param>
/// <param name="params"> vectorID, value </param>
/// <returns> Returns the prev element for the given value. If doesn't exists a prev one, it returns -1 </returns>

static cell AMX_NATIVE_CALL n_Vector_Prev(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() < 2 || vectors[static_cast<unsigned long int>(params[1]) - 1].count(static_cast<int>(params[2])) == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	//auto it = std::prev(vectors[vectorID].find(static_cast<int>(params[2])));
	auto it = vectors[vectorID].find(static_cast<int>(params[2]));
	std::advance(it, -1);
	if (debugging) logprintf("%s: Returning the value %d for vector %d, given value %d.", pluginutils::GetCurrentNativeFunctionName(amx), *it, vectorID + 1, static_cast<int>(params[2]));
	return *it;
}

/// <summary>
/// Returns the prev element for the given value.
/// </summary>
/// <param name="amx"> Vector_Prev </param>
/// <param name="params"> vectorID, value </param>
/// <returns> Returns the prev element for the given value. If doesn't exists a prev one, it returns -1 </returns>

int randInt(int n) {
	if (n - 1 == RAND_MAX) {
		return rand();
	}
	else {
		assert(n <= RAND_MAX);

		auto end = RAND_MAX / n;
		assert(end > 0);
		end *= n;
		auto r = rand();
		while (r >= end) r = rand();
		return r % n;
	}
}

static cell AMX_NATIVE_CALL n_Vector_Random(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	auto number = randInt(vectors[vectorID].size());
	if (debugging) logprintf("%s: Returning the value %d for vector %d.", pluginutils::GetCurrentNativeFunctionName(amx), copy_vectors[vectorID][number], vectorID + 1);
	return copy_vectors[vectorID][number];
}

/// <summary>
/// Removes the last element of vector and returns it.
/// </summary>
/// <param name="amx"> Vector_PopBack </param>
/// <param name="params"> vectorID </param>
/// <returns> Removes the last element of vector and returns it. </returns>

static cell AMX_NATIVE_CALL n_Vector_PopBack(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	int value = copy_vectors[vectorID][copy_vectors[vectorID].size() - 1];
	vectors[vectorID].erase(vectors[vectorID].end());
	copy_vectors[vectorID].erase(copy_vectors[vectorID].end());
	if (debugging) logprintf("%s: Returning the value %d for vector %d after removing it.", pluginutils::GetCurrentNativeFunctionName(amx), value, vectorID + 1);
	return value;
}

/// <summary>
/// Removes the first element of vector and returns it.
/// </summary>
/// <param name="amx"> Vector_PopFront </param>
/// <param name="params"> vectorID </param>
/// <returns> Removes the first element of vector and returns it. </returns>

static cell AMX_NATIVE_CALL n_Vector_PopFront(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	auto it = vectors[vectorID].begin();
	vectors[vectorID].erase(it);
	copy_vectors[vectorID].erase(copy_vectors[vectorID].begin());
	if (debugging) logprintf("%s: Returning the value %d for vector %d after removing it.", pluginutils::GetCurrentNativeFunctionName(amx), *it, vectorID + 1);
	return *it;
}

/// <summary>
/// Find element at given index.
/// </summary>
/// <param name="amx"> Vector_FindValue </param>
/// <param name="params"> vectorID, index </param>
/// <returns> Returns the element value at given index. If it doesn't exists, it returns -1. </returns>

static cell AMX_NATIVE_CALL n_Vector_FindValue(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (static_cast<unsigned long int>(params[2]) < 0 || static_cast<unsigned long int>(params[2]) >= vectors[static_cast<unsigned long int>(params[1]) - 1].size() || vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	int value = copy_vectors[vectorID][static_cast<int>(params[2])];
	if (debugging) logprintf("%s: Returning the value %d for vector %d after searching at index %d.", pluginutils::GetCurrentNativeFunctionName(amx), value, vectorID + 1, static_cast<unsigned long int>(params[2]));
	return value;
}

/// <summary>
/// Find index at given value.
/// </summary>
/// <param name="amx"> Vector_FindIndex </param>
/// <param name="params"> vectorID, value </param>
/// <returns> Returns the index at given element. If it doesn't exists, it returns -1. </returns>

static cell AMX_NATIVE_CALL n_Vector_FindIndex(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0 || vectors[static_cast<unsigned long int>(params[1]) - 1].count(static_cast<int>(params[2])) == 0) {
		if (debugging) logprintf("%s: No element found with value %d in vector %d, returning -1.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<unsigned long int>(params[2]), static_cast<unsigned long int>(params[1]));
		return -1;
	}

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	int index = std::distance(copy_vectors[vectorID].begin(), std::lower_bound(copy_vectors[vectorID].begin(), copy_vectors[vectorID].end(), static_cast<int>(params[2])));
	if (debugging) logprintf("%s: Returning the value %d for vector %d after searching for element %d.", pluginutils::GetCurrentNativeFunctionName(amx), index, vectorID + 1, static_cast<unsigned long int>(params[2]));
	return index;
}

/// <summary>
/// Replacing value.
/// </summary>
/// <param name="amx"> Vector_ReplaceIndex </param>
/// <param name="params"> vectorID, index, new_value </param>
/// <returns> Replaces the value at given index with new_value. If index is invalid, it returns -1 </returns>

static cell AMX_NATIVE_CALL n_Vector_ReplaceIndex(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (static_cast<unsigned long int>(params[2]) < 0 || static_cast<unsigned long int>(params[2]) >= vectors[static_cast<unsigned long int>(params[1]) - 1].size() || vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	int replaced = *(std::next(vectors[vectorID].begin(), static_cast<int>(params[2])));

	copy_vectors[vectorID][static_cast<int>(params[2])] = static_cast<int>(params[3]);
	vectors[vectorID].clear();
	for (const int& i : copy_vectors[vectorID])
		vectors[vectorID].insert(i);
	
	if (debugging) logprintf("%s: Replacing value %d with %d in vector %d with index %d.", pluginutils::GetCurrentNativeFunctionName(amx), replaced, static_cast<unsigned long int>(params[3]), vectorID + 1, static_cast<unsigned long int>(params[2]));
	return 1;
}

/// <summary>
/// Replacing value.
/// </summary>
/// <param name="amx"> Vector_Replace </param>
/// <param name="params"> vectorID, old_value, new_value </param>
/// <returns> Replaces the old_value with new_value. If old_value doesn't exists, it returns -1 </returns>

static cell AMX_NATIVE_CALL n_Vector_Replace(AMX* amx, cell* params)
{
	unsigned short int num_args = 1;
	if (!pluginutils::CheckNumberOfArguments(amx, params, num_args))
		return 0;
	if (static_cast<unsigned long int>(params[1]) < 1 || static_cast<unsigned long int>(params[1]) > vctID)
		return -1;
	if (vectors[static_cast<unsigned long int>(params[1]) - 1].size() == 0)
		return -1;

	unsigned long int vectorID = static_cast<unsigned long int>(params[1]) - 1;
	auto it = vectors[vectorID].find(static_cast<int>(params[2]));
	if (it == vectors[vectorID].end()) {
		if (debugging) logprintf("%s: No element found with value %d in vector %d, returning -1.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<unsigned long int>(params[2]), vectorID + 1);
		return -1;
	}
	int index = std::distance(vectors[vectorID].begin(), it);
	
	copy_vectors[vectorID][index] = static_cast<int>(params[3]);
	vectors[vectorID].clear();
	for (const int& i : copy_vectors[vectorID])
		vectors[vectorID].insert(i);

	if (debugging) logprintf("%s: Replacing value %d with %d in vector %d with index %d.", pluginutils::GetCurrentNativeFunctionName(amx), static_cast<int>(params[2]), static_cast<unsigned long int>(params[3]), vectorID + 1, index);
	return 1;
}

static AMX_NATIVE_INFO plugin_natives[] =
{
	{ "Vector_Create", n_Vector_Create },
	{ "Vector_DebugMode", n_Vector_DebugMode },
	{ "Vector_Size", n_Vector_Size },
	{ "Vector_Odd", n_Vector_Odd },
	{ "Vector_Even", n_Vector_Even },
	{ "Vector_Empty", n_Vector_Empty },
	{ "Vector_Add", n_Vector_Add },
	{ "Vector_Clear", n_Vector_Clear },
	{ "Vector_Remove", n_Vector_Remove },
	{ "Vector_Delete", n_Vector_Delete },
	{ "Vector_Begin", n_Vector_Begin },
	{ "Vector_End", n_Vector_End },
	{ "Vector_First", n_Vector_First },
	{ "Vector_Last", n_Vector_Last },
	{ "Vector_Next", n_Vector_Next },
	{ "Vector_Prev", n_Vector_Prev },
	{ "Vector_Random", n_Vector_Random },
	{ "Vector_PopBack", n_Vector_PopBack },
	{ "Vector_PopFront", n_Vector_PopFront },
	{ "Vector_FindIndex", n_Vector_FindIndex },
	{ "Vector_FindValue", n_Vector_FindValue },
	{ "Vector_ReplaceIndex", n_Vector_ReplaceIndex },
	{ "Vector_Replace", n_Vector_Replace }
};


PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return PLUGIN_SUPPORTS_FLAGS;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (void *(*)(const char *fmt, ...))ppData[PLUGIN_DATA_LOGPRINTF];
	if (NULL == pAMXFunctions || NULL == logprintf)
		return false;
	int plug_ver_major, plug_ver_minor, plug_ver_build;
	pluginutils::SplitVersion(PLUGIN_VERSION, plug_ver_major, plug_ver_minor, plug_ver_build);
	logprintf("  ");
	logprintf("  %s plugin v%d.%d.%d is OK", PLUGIN_NAME, plug_ver_major, plug_ver_minor, plug_ver_build);
	logprintf("  ");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf("  %s plugin was unloaded", PLUGIN_NAME);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	if (!pluginutils::CheckIncludeVersion(amx))
		return 0;

	amx_Register(amx, plugin_natives, (int)arraysize(plugin_natives));
	return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	vctID = 0;
	vectors.clear();
	copy_vectors.clear();
	return AMX_ERR_NONE;
}

/*
PLUGIN_EXPORT int PLUGIN_CALL ProcessTick()
{
	return AMX_ERR_NONE;
}
*/
