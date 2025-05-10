The purpose of this repository is gain a little experience with clang's thread-safety analysis feature by extending the [example code](https://releases.llvm.org/19.1.0/tools/clang/docs/ThreadSafetyAnalysis.html) provided at the project website.

The reason for interest is to learn to annotate and analyze the [librtpi alternative pthread library](https://gitlab.com/linux-rt/librtpi.git) which [thread sanitizer](https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual) (TSAN) is unable to comprehend.
