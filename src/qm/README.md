# QM Directory

This is where the `.qm` file goes, and nothing else. You should not modify the
`.qm` file outside of QM itself.

This example `dishwasher_controller.qm` file contains the minimal `dishwasher_sm.c` and
`dishwasher_sm.h` templates, which are configured to be generated inside the
`qm_generated` directory.

Once you build your state machine in QM, where you should only need to call
functions written in either the BSP or a helper file in the app directory,
you can click the Generate Code button to cause the generated code files to be
updated.

You need to be careful when using JetBrains refactoring that the `qm_generated`
files are not updated - they are set to read only by QM, so it's best to respect
that.
