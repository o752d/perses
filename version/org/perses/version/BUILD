package(default_visibility = [
    "//visibility:public",
])

load("@io_bazel_rules_kotlin//kotlin:kotlin.bzl", "kt_jvm_binary", "kt_jvm_library")

kt_jvm_library(
    name = "version_class_generator",
    srcs = ["VersionClassGenerator.kt"],
    deps = [
        "@maven//:com_google_guava_guava",
    ],
)

java_binary(
    name = "version_class_generator_main",
    srcs = ["VersionClassGeneratorMain.java"],
    jvm_flags = ["-ea"],
    main_class = "org.perses.version.VersionClassGeneratorMain",
    visibility = ["//visibility:private"],
    deps = [
        ":version_class_generator",
    ],
)

genrule(
    name = "generate_version_class",
    srcs = ["@local_jdk//:jdk"],
    outs = ["Version.kt"],
    cmd = "$(location :version_class_generator_main) bazel-out/volatile-status.txt $@",
    stamp = True,
    tools = [":version_class_generator_main"],
)

kt_jvm_library(
    name = "version",
    srcs = [
        "Version.kt",
        "VersionHelper.kt",
    ],
)
