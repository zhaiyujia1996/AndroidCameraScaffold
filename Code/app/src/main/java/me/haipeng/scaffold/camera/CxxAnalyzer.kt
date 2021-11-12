@file:Suppress("SpellCheckingInspection")

package me.haipeng.scaffold.camera

import me.haipeng.scaffold.camera.cxx.CxxEntrance

/**
 * @author ZhengHaiPeng
 * @since 2021/11/12 10:00 下午
 */
class CxxAnalyzer : AbsAnalyzer() {

    /* ======================================================= */
    /* Override/Implements Methods                             */
    /* ======================================================= */

    override fun onAnalyze(pixels: IntArray) {
        CxxEntrance.onCameraPreviewUpdate(pixels)
    }
}