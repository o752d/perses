package(default_visibility = [
    "//visibility:public",
])

# TODO: need to split this target. It is too big. For example, tree_node, tree_edit_actions, tree_and_tree_edit

java_library(
    name = "spar",
    srcs = glob(["*.java"]),
    deps = [
        "//src/org/perses/antlr",
        "//src/org/perses/program",
        "//src/org/perses/util",
        "@maven//:com_google_guava_guava",
        "@maven//:org_antlr_antlr4_runtime",
        "@maven//:org_checkerframework_checker_qual",
    ],
)
