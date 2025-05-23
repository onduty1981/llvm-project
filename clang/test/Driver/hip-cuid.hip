// Check invalid -fuse-cuid= option.

// RUN: not %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-arch=gfx906 \
// RUN:   -c -nogpuinc -nogpulib -fuse-cuid=invalid \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=INVALID %s

// Check random CUID generator.

// RUN: %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-arch=gfx906 \
// RUN:   -c -nogpuinc -nogpulib -fuse-cuid=random \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=COMMON,HEX %s

// Check fixed CUID.

// RUN: %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-arch=gfx906 \
// RUN:   -c -nogpuinc -nogpulib -cuid=xyz_123 \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=COMMON,FIXED %s

// Check fixed CUID override -fuse-cuid.

// RUN: %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-arch=gfx906 \
// RUN:   -c -nogpuinc -nogpulib -fuse-cuid=random -cuid=xyz_123 \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=COMMON,FIXED %s

// Check hash CUID generator.

// RUN: %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-arch=gfx906 \
// RUN:   -c -nogpuinc -nogpulib -fuse-cuid=hash \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=COMMON,HEX %s

// Check that cuid is propagated to the host-only compilation.
// RUN: %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-host-only \
// RUN:   -c -nogpuinc -nogpulib -cuid=xyz_123 \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=HOST %s

// Check that cuid is propagated to the device-only compilation.
// RUN: %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-device-only \
// RUN:   -c -nogpuinc -nogpulib -cuid=xyz_123 \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=DEVICE %s

// Check cuid is supported by the new driver.
// RUN: %clang -### -x hip \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --no-offload-new-driver \
// RUN:   --offload-arch=gfx900 \
// RUN:   --offload-arch=gfx906 \
// RUN:   -c -nogpuinc -nogpulib --offload-new-driver \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=COMMON,HEX %s

// Check cuid is supported by CUDA by the default new driver.
// RUN: %clang -### -x cu \
// RUN:   --target=x86_64-unknown-linux-gnu \
// RUN:   --offload-arch=sm_60 \
// RUN:   --offload-arch=sm_70 \
// RUN:   -c -nogpuinc -nogpulib \
// RUN:   %S/Inputs/hip_multiple_inputs/a.cu \
// RUN:   %S/Inputs/hip_multiple_inputs/b.hip \
// RUN: 2>&1 | FileCheck -check-prefixes=COMMON,HEX %s

// INVALID: invalid value 'invalid' in '-fuse-cuid=invalid'

// COMMON: "-cc1"{{.*}} "-triple" "[[TRIP:(amdgcn-amd-amdhsa|nvptx64-nvidia-cuda)]]"
// COMMON-SAME: "-target-cpu" "[[G1:(gfx900|sm_60)]]"
// HEX-SAME: "-cuid=[[CUID:[0-9a-f]+]]"
// FIXED-SAME: "-cuid=[[CUID:xyz_123]]"
// COMMON-SAME: "{{.*}}a.cu"

// COMMON: "-cc1"{{.*}} "-triple" "[[TRIP]]"
// COMMON-SAME: "-target-cpu" "[[G2:(gfx906|sm_70)]]"
// COMMON-SAME: "-cuid=[[CUID]]"
// COMMON-SAME: "{{.*}}a.cu"

// COMMON: "-cc1"{{.*}} "-triple" "x86_64-unknown-linux-gnu"
// COMMON-SAME: "-cuid=[[CUID]]"
// COMMON-SAME: "{{.*}}a.cu"

// COMMON: "-cc1"{{.*}} "-triple" "[[TRIP]]"
// COMMON-SAME: "-target-cpu" "[[G1]]"
// HEX-NOT: "-cuid=[[CUID]]"
// HEX-SAME: "-cuid=[[CUID2:[0-9a-f]+]]"
// FIXED-SAME: "-cuid=[[CUID2:xyz_123]]"
// COMMON-SAME: "{{.*}}b.hip"

// COMMON: "-cc1"{{.*}} "-triple" "[[TRIP]]"
// COMMON-SAME: "-target-cpu" "[[G2]]"
// HEX-NOT: "-cuid=[[CUID]]"
// COMMON-SAME: "-cuid=[[CUID2]]"
// COMMON-SAME: "{{.*}}b.hip"

// COMMON: "-cc1"{{.*}} "-triple" "x86_64-unknown-linux-gnu"
// HEX-NOT: "-cuid=[[CUID]]"
// COMMON-SAME: "-cuid=[[CUID2]]"
// COMMON-SAME: "{{.*}}b.hip"

// HOST: "-cc1"{{.*}} "-triple" "x86_64-unknown-linux-gnu"
// HOST-SAME: "-cuid=[[CUID:xyz_123]]"
// HOST-SAME: "{{.*}}a.cu"

// HOST: "-cc1"{{.*}} "-triple" "x86_64-unknown-linux-gnu"
// HOST-SAME: "-cuid=[[CUID]]"
// HOST-SAME: "{{.*}}b.hip"

// DEVICE: "-cc1"{{.*}} "-triple" "amdgcn-amd-amdhsa"
// DEVICE-SAME: "-target-cpu" "gfx900"
// DEVICE-SAME: "-cuid=[[CUID:xyz_123]]"
// DEVICE-SAME: "{{.*}}a.cu"

// DEVICE: "-cc1"{{.*}} "-triple" "amdgcn-amd-amdhsa"
// DEVICE-SAME: "-target-cpu" "gfx900"
// DEVICE-SAME: "-cuid=[[CUID]]"
// DEVICE-SAME: "{{.*}}b.hip"
