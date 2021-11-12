package me.haipeng.scaffold.camera.cxx;

import java.util.HashMap;
import java.util.Map;

import android.util.Log;

/**
 * @author ZhengHaiPeng
 * @since 6/8/21 4:08 PM
 */
@SuppressWarnings("unused")
public class CxxEntrance {

    /* ======================================================= */
    /* Fields                                                  */
    /* ======================================================= */

    /**
     * 保存可以供 C++ 调用的方法列表。
     */
    private final static Map<String, CxxRequestHandler> functions = new HashMap<>();

    static {

        Log.i("ZHP_TEST", "即将加载 libCxxEntrance.so ...");
        System.loadLibrary("CxxEntrance");
        Log.i("ZHP_TEST", "加载 libCxxEntrance.so 完毕！");

        // 注册内置方法： 验证 C++ 可以调通 Java
        CxxEntrance.registerFunctions(
            "Hello Java, I'm C++",
            (params)-> "0000" + "Hi, I received you message!"
        );

    }



    /* ======================================================= */
    /* Public Native Methods                                   */
    /* ======================================================= */

    /**
     * 调用 C++ 的方法。
     */
    public static native String javaCallCxx(String action, String params);

    /**
     * 相机预览画面改变时传递到 C++ 层。
     */
    public static native void onCameraPreviewUpdate(int[] pixels);



    /* ======================================================= */
    /* Public Methods                                          */
    /* ======================================================= */

    /**
     * 不带参数的 java 调用 C++。
     */
    public static String javaCallCxx(String action) {
        return javaCallCxx(action, "");
    }

    /**
     * C++ 调用 Java 的方法
     */
    public static String cxxCallJava(String action, String params) {
        CxxRequestHandler handler = functions.get(action);
        if (handler == null) {
            return "";
        }

        String res = handler.invoke(params);
        if (res == null) {
            return "";
        }

        return res;
    }

    /**
     * 注册供 C++ 调用的方法。
     */
    public static void registerFunctions(String action, CxxRequestHandler handler) {
        functions.put(action, handler);
    }



    /* ======================================================= */
    /* Private Methods                                         */
    /* ======================================================= */

    private static String onCxxCallHello(String params) {
        return "0001";
    }



    /* ======================================================= */
    /* Inner Class                                             */
    /* ======================================================= */

    /**
     * 处理 C++ 的请求。
     */
    public interface CxxRequestHandler {
        String invoke(String params);
    }
}