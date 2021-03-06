



import java.io.*;
import java.util.*;

public class Main
{
    File testSrc = new File(System.getProperty("test.src"));

    public static void main(String[] args) throws Exception {
        new Main().run();
    }

    public void run() throws Exception {

        
        compile(true, "Test.java");

        

        List<String> base_files = Arrays.asList(
            "Boolean.java",
            "Byte.java",
            "Character.java",
            "Integer.java",
            "Long.java",
            "Number.java",
            "Object.java",
            "Short.java",
            "Void.java"
        );

        List<String> extra_files = Arrays.asList(
            "Double.java",
            "Float.java",
            "Cloneable.java",
            "Serializable.java"
        );

        List<String> files = new ArrayList<String>();
        files.addAll(base_files);
        files.add("Test.java");

        compile(false, files);

        for (String f: extra_files) {
            files = new ArrayList<String>();
            files.addAll(base_files);
            files.addAll(extra_files);
            files.remove(f);
            files.add("Test.java");
            compile(false, files);
        }

        if (errors > 0)
            throw new Exception(errors + " errors occurred");
    }

    void compile(boolean stdBootClassPath, String... files) {
        compile(stdBootClassPath, Arrays.asList(files));
    }

    void compile(boolean stdBootClassPath, List<String> files) {
        File empty = new File("empty");
        empty.mkdirs();

        List<String> args = new ArrayList<String>();
        args.add("-classpath");
        args.add("empty");

        if (!stdBootClassPath) {
            args.add("-bootclasspath");
            args.add("empty");
        }
        args.add("-d");
        args.add(".");
        for (String f: files)
            args.add(new File(testSrc, f).getPath());

        System.out.println("Compile: " + args);
        StringWriter out = new StringWriter();
        int rc = com.sun.tools.javac.Main.compile(args.toArray(new String[args.size()]),
                                                  new PrintWriter(out));
        System.out.println(out.toString());
        System.out.println("result: " + rc);
        System.out.println();

        if (rc != 0)
            errors++;
    }

    private int errors;
}


