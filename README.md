This is a fork of syclinfo from lluhad.  I have modified it to make it compatible with SYCL 2020 and with icpx compiler (dpc++).

# syclinfo - a simple tool to query SYCL devices and platforms

`syclinfo` queries all SYCL devices and platforms for all available information. In that sense, it is the SYCL equivalent to the well-known `clinfo` for OpenCL. Like `clinfo`, `syclinfo` is particularly useful to quickly check the functionality of SYCL installations and devices.

## Installing
`syclinfo` has been tested with dpc++ SYCL implementations. 
```
$ mkdir <build directory>; cd <build directory>
$ cmake ..
$ make
```

### Sample Output

```
$ ./syclinfo

***************************************
           Platform:                   
***************************************
name: Intel(R) Level-Zero
vendor: Intel(R) Corporation
version: 1.3
profile: FULL_PROFILE

============ Found device: =============
name: Intel(R) Iris(R) Xe Graphics
vendor: Intel(R) Corporation
driver_version: 1.3.26516
version: 1.3
opencl_c_version: 
device_type: GPU
vendor_id: 32902
is_available: 1
max_compute_units: 96
max_work_item_dimensions: 3
max_work_group_size: 512
sub_group_sizes: 8, 16, 32
preferred_vector_width_char: 8
preferred_vector_width_short: 4
preferred_vector_width_int: 2
preferred_vector_width_long: 1
preferred_vector_width_float: 2
preferred_vector_width_double: 1
preferred_vector_width_half: 4
native_vector_width_char: 8
native_vector_width_short: 4
native_vector_width_int: 2
native_vector_width_long: 1
native_vector_width_float: 2
native_vector_width_double: 1
native_vector_width_half: 4
max_clock_frequency: 1300
address_bits: 64
max_mem_alloc_size: 4294959104
image_support: yes
max_read_image_args: 128
max_write_image_args: 128
image2d_max_height: 16384
image2d_max_width: 16384
image3d_max_height: 2048
image3d_max_width: 2048
image3d_max_depth: 2048
image_max_buffer_size: 268434944
image_max_array_size: 2048
max_samplers: 16
max_parameter_size: 2048
mem_base_addr_align: 8
half_fp_config: inf_nan, round_to_nearest, round_to_zero, round_to_inf, fma, soft_float
single_fp_config: inf_nan, round_to_nearest, round_to_zero, round_to_inf, fma, soft_float
double_fp_config: 
global_mem_cache_type: Write-only
global_mem_cache_line_size: 1
global_mem_cache_size: 3932160
global_mem_size: 26549178368
local_mem_type: Local
local_mem_size: 65536
usm_device_allocations: yes
usm_host_allocations: yes
usm_shared_allocations: yes
usm_system_allocations: no
atomic_memory_order_capabilities: relaxed, acquire, release, acq_rel, seq_cst
atomic_fence_order_capabilities: relaxed, acquire, release, acq_rel, seq_cst
atomic_memory_scope_capabilities: work_item, sub_group, work_group, device, system
atomic_fence_scope_capabilities: work_item, sub_group, work_group, device, system
error_correction_support: 0
profiling_timer_resolution: 52
is_compiler_available: yes
is_linker_available: yes
execution_capabilities: exec_native_kernel
queue_profiling: yes
built_in_kernel_ids: 
partition_max_sub_devices: 0
partition_properties: no_partition
partition_affinity_domains: numa, next_partitionable
partition_type_property: no_partition
partition_type_affinity_domain: not_applicable
reference_count: 1

============ Intel Extensions: =============
ext_intel_gpu_slices: 1
ext_intel_gpu_eu_count: 96
ext_intel_gpu_eu_simd_width: 8
ext_intel_gpu_subslices_per_slice: 6
ext_intel_gpu_eu_count_per_subslice: 16
ext_intel_gpu_hw_threads_per_eu: 7

```
