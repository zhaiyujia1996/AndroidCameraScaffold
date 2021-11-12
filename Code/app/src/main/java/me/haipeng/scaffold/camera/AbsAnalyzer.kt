@file:Suppress("SpellCheckingInspection")

package me.haipeng.scaffold.camera

import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy
import java.nio.ByteBuffer

/**
 * @author ZhengHaiPeng
 * @since 2021/11/12 9:55 下午
 */
abstract class AbsAnalyzer : ImageAnalysis.Analyzer {

    /* ======================================================= */
    /* Override/Implements Methods                             */
    /* ======================================================= */

    override fun analyze(image: ImageProxy) {
        val buffer = image.planes[0].buffer
        val data = buffer.toByteArray()
        val pixels = IntArray(data.size) {
            data[it].toInt() and 0xFF
        }
        onAnalyze(pixels)
        image.close()
    }



    /* ======================================================= */
    /* Public Methods                                          */
    /* ======================================================= */

    abstract fun onAnalyze(pixels: IntArray)




    /* ======================================================= */
    /* Extensions Methods                                      */
    /* ======================================================= */

    private fun ByteBuffer.toByteArray(): ByteArray {
        rewind()
        val data = ByteArray(remaining())
        get(data)
        return data
    }
}