#pragma once
#include <cstdint>

#ifdef ANDROID
#define __cdecl
#endif

#define PUBLIC_KEY_BYTE_LENGTH 8

typedef struct Il2CppAssemblyName
{
	const char* name;
	const char* culture;
	const char* hash_value;
	const char* public_key;
	uint32_t hash_alg;
	int32_t hash_len;
	uint32_t flags;
	int32_t major;
	int32_t minor;
	int32_t build;
	int32_t revision;
	uint8_t public_key_token[PUBLIC_KEY_BYTE_LENGTH];
} Il2CppAssemblyName;

typedef struct Il2CppAssembly
{
	//Il2CppImage* image;
	void* image;
	uint32_t token;
	int32_t referencedAssemblyStart;
	int32_t referencedAssemblyCount;
	Il2CppAssemblyName aname;
} Il2CppAssembly;

#pragma region NotDefined
//typedef struct VirtualInvokeData
//{
//    Il2CppMethodPointer methodPtr;
//#if RUNTIME_MONO
//    const MonoMethod* method;
//#else
//    const MethodInfo* method;
//#endif
//} VirtualInvokeData;
//
//typedef struct Il2CppClass
//{
//    // The following fields are always valid for a Il2CppClass structure
//    const void* image;
//    void* gc_desc;
//    const char* name;
//    const char* namespaze;
//    Il2CppType byval_arg;
//    Il2CppType this_arg;
//    Il2CppClass* element_class;
//    Il2CppClass* castClass;
//    Il2CppClass* declaringType;
//    Il2CppClass* parent;
//    Il2CppGenericClass* generic_class;
//    const Il2CppTypeDefinition* typeDefinition; // non-NULL for Il2CppClass's constructed from type defintions
//    const Il2CppInteropData* interopData;
//    Il2CppClass* klass; // hack to pretend we are a MonoVTable. Points to ourself
//    // End always valid fields
//
//    // The following fields need initialized before access. This can be done per field or as an aggregate via a call to Class::Init
//    FieldInfo* fields; // Initialized in SetupFields
//    const EventInfo* events; // Initialized in SetupEvents
//    const PropertyInfo* properties; // Initialized in SetupProperties
//    const MethodInfo** methods; // Initialized in SetupMethods
//    Il2CppClass** nestedTypes; // Initialized in SetupNestedTypes
//    Il2CppClass** implementedInterfaces; // Initialized in SetupInterfaces
//    Il2CppRuntimeInterfaceOffsetPair* interfaceOffsets; // Initialized in Init
//    void* static_fields; // Initialized in Init
//    const Il2CppRGCTXData* rgctx_data; // Initialized in Init
//    // used for fast parent checks
//    Il2CppClass** typeHierarchy; // Initialized in SetupTypeHierachy
//    // End initialization required fields
//
//    uint32_t initializationExceptionGCHandle;
//
//    uint32_t cctor_started;
//    uint32_t cctor_finished;
//    ALIGN_TYPE(8) uint64_t cctor_thread;
//
//    // Remaining fields are always valid except where noted
//    GenericContainerIndex genericContainerIndex;
//    uint32_t instance_size;
//    uint32_t actualSize;
//    uint32_t element_size;
//    int32_t native_size;
//    uint32_t static_fields_size;
//    uint32_t thread_static_fields_size;
//    int32_t thread_static_fields_offset;
//    uint32_t flags;
//    uint32_t token;
//
//    uint16_t method_count; // lazily calculated for arrays, i.e. when rank > 0
//    uint16_t property_count;
//    uint16_t field_count;
//    uint16_t event_count;
//    uint16_t nested_type_count;
//    uint16_t vtable_count; // lazily calculated for arrays, i.e. when rank > 0
//    uint16_t interfaces_count;
//    uint16_t interface_offsets_count; // lazily calculated for arrays, i.e. when rank > 0
//
//    uint8_t typeHierarchyDepth; // Initialized in SetupTypeHierachy
//    uint8_t genericRecursionDepth;
//    uint8_t rank;
//    uint8_t minimumAlignment; // Alignment of this type
//    uint8_t naturalAligment; // Alignment of this type without accounting for packing
//    uint8_t packingSize;
//
//    // this is critical for performance of Class::InitFromCodegen. Equals to initialized && !has_initialization_error at all times.
//    // Use Class::UpdateInitializedAndNoError to update
//    uint8_t initialized_and_no_error : 1;
//
//    uint8_t valuetype : 1;
//    uint8_t initialized : 1;
//    uint8_t enumtype : 1;
//    uint8_t is_generic : 1;
//    uint8_t has_references : 1;
//    uint8_t init_pending : 1;
//    uint8_t size_inited : 1;
//    uint8_t has_finalize : 1;
//    uint8_t has_cctor : 1;
//    uint8_t is_blittable : 1;
//    uint8_t is_import_or_windows_runtime : 1;
//    uint8_t is_vtable_initialized : 1;
//    uint8_t has_initialization_error : 1;
//    VirtualInvokeData vtable[IL2CPP_ZERO_LEN_ARRAY];
//} Il2CppClass;
//
//typedef void (*Il2CppMethodPointer)();
//typedef void* (*InvokerMethod)(Il2CppMethodPointer, const MethodInfo*, void*, void**);
//
//typedef struct MethodInfo
//{
//	Il2CppMethodPointer methodPointer;
//	InvokerMethod invoker_method;
//	const char* name;
//	Il2CppClass* klass;
//	const Il2CppType* return_type;
//	const ParameterInfo* parameters;
//
//	union
//	{
//		const Il2CppRGCTXData* rgctx_data; /* is_inflated is true and is_generic is false, i.e. a generic instance method */
//		const Il2CppMethodDefinition* methodDefinition;
//	};
//
//	/* note, when is_generic == true and is_inflated == true the method represents an uninflated generic method on an inflated type. */
//	union
//	{
//		const Il2CppGenericMethod* genericMethod; /* is_inflated is true */
//		const Il2CppGenericContainer* genericContainer; /* is_inflated is false and is_generic is true */
//	};
//
//	uint32_t token;
//	uint16_t flags;
//	uint16_t iflags;
//	uint16_t slot;
//	uint8_t parameters_count;
//	uint8_t is_generic : 1; /* true if method is a generic method definition */
//	uint8_t is_inflated : 1; /* true if declaring_type is a generic instance or if method is a generic instance*/
//	uint8_t wrapper_type : 1; /* always zero (MONO_WRAPPER_NONE) needed for the debugger */
//	uint8_t is_marshaled_from_native : 1; /* a fake MethodInfo wrapping a native function pointer */
//} MethodInfo;
#pragma endregion 

#if defined(__cplusplus)
extern "C"
{
#endif
	//domain
	//DO_API(Il2CppDomain*, il2cpp_domain_get, ());
	typedef void* (__cdecl* il2cpp_domain_get)();
	//DO_API(const Il2CppAssembly**, il2cpp_domain_get_assemblies, (const Il2CppDomain * domain, size_t * size));
	typedef const Il2CppAssembly** (__cdecl* il2cpp_domain_get_assemblies)(const void* domain, size_t* size); //uintptr_t

	//thread
	//DO_API(Il2CppThread*, il2cpp_thread_current, ());
	typedef void* (__cdecl* il2cpp_thread_current)();
	//DO_API(Il2CppThread*, il2cpp_thread_attach, (Il2CppDomain* domain));
	typedef void* (__cdecl* il2cpp_thread_attach)(void* domain);
	//DO_API(void, il2cpp_thread_detach, (Il2CppThread * thread));
	typedef void (__cdecl* il2cpp_thread_detach)(void* thread);

	// assembly
	//DO_API(const Il2CppImage*, il2cpp_assembly_get_image, (const Il2CppAssembly* assembly));
	typedef const void* (__cdecl* il2cpp_assembly_get_image)(const Il2CppAssembly* assembly);
	
	//image
	//DO_API(const Il2CppAssembly*, il2cpp_image_get_assembly, (const Il2CppImage * image));
	typedef const Il2CppAssembly* (__cdecl* il2cpp_image_get_assembly)(const void* image);
	//DO_API(const char*, il2cpp_image_get_name, (const Il2CppImage * image));
	typedef const char* (__cdecl* il2cpp_image_get_name)(const void* image);
	//DO_API(const char*, il2cpp_image_get_filename, (const Il2CppImage * image));
	typedef const char* (__cdecl* il2cpp_image_get_filename)(const void* image);

	//DO_API(size_t, il2cpp_image_get_class_count, (const Il2CppImage * image));
	typedef size_t (__cdecl* il2cpp_image_get_class_count)(const void* image);
	//DO_API(const Il2CppClass*, il2cpp_image_get_class, (const Il2CppImage* image, size_t index));
	typedef const void* (__cdecl* il2cpp_image_get_class)(const void* image, size_t index);

	//class
	//DO_API(const char*, il2cpp_class_get_name, (Il2CppClass* klass));
	typedef const char* (__cdecl* il2cpp_class_get_name)(void* klass);
	//DO_API(const char*, il2cpp_class_get_namespace, (Il2CppClass* klass));
	typedef const char* (__cdecl* il2cpp_class_get_namespace)(void* klass);
	//DO_API(Il2CppClass*, il2cpp_class_from_name, (const Il2CppImage * image, const char* namespaze, const char *name));
	typedef void* (__cdecl* il2cpp_class_from_name)(const void* image, const char* namespaze, const char* name);
	//DO_API(const MethodInfo*, il2cpp_class_get_method_from_name, (Il2CppClass * klass, const char* name, int argsCount));
	typedef void* (__cdecl* il2cpp_class_get_method_from_name)(void* klass, const char* name, int argsCount);

	//method
	//DO_API(const char*, il2cpp_method_get_name, (const MethodInfo* method));
	typedef const char* (__cdecl* il2cpp_method_get_name)(const void* method);
	//DO_API(Il2CppClass*, il2cpp_method_get_class, (const MethodInfo * method));
	typedef void* (__cdecl* il2cpp_method_get_class)(const void* method);
#if defined(__cplusplus)
}
#endif // __cplusplus