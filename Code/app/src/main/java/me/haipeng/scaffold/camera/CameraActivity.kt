@file:Suppress("SpellCheckingInspection")

package me.haipeng.scaffold.camera

import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.camera.core.CameraSelector
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.Preview
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.camera.view.PreviewView
import androidx.core.content.ContextCompat
import me.haipeng.scaffold.camera.cxx.CxxEntrance
import java.lang.Exception
import java.util.concurrent.Executors


/**
 * 相机画面预览界面。
 *
 * @author ZhengHaiPeng
 * @since  2021年11月12日21:32:52
 */
class CameraActivity : AppCompatActivity() {

    /* ======================================================= */
    /* Fields                                                  */
    /* ======================================================= */

    /**
     * 预览画面
     */
    private lateinit var viewFinder: PreviewView

    private lateinit var provider: ProcessCameraProvider

    private val cameraExecutor by lazy { Executors.newSingleThreadExecutor() }



    /* ======================================================= */
    /* Override/Implements Methods                             */
    /* ======================================================= */

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.scaffold_activity_camera)
        initViews()
        initCamera()
        initCxx()
    }

    override fun onStop() {
        super.onStop()
        CxxEntrance.javaCallCxx("OnCameraClosed")
    }



    /* ======================================================= */
    /* Private Methods                                         */
    /* ======================================================= */

    private fun initViews() {
        // 返回按钮
        val backButton = findViewById<Button>(R.id.backButton)
        backButton.setOnClickListener {
            onBackPressed()
        }

        // 预览界面
        viewFinder = findViewById(R.id.viewFinder)
    }

    private fun initCamera() {
        val future = ProcessCameraProvider.getInstance(this)
        future.addListener({
            onCameraReady(future.get())
        }, ContextCompat.getMainExecutor(this))
    }

    private fun onCameraReady(provider: ProcessCameraProvider) {
        this.provider = provider

        // 预览
        val preview = Preview.Builder().build()
        preview.setSurfaceProvider(this.viewFinder.surfaceProvider)

        // 分析
        val analyzer = ImageAnalysis.Builder()
            .build()
            .also {
                it.setAnalyzer(cameraExecutor, CxxAnalyzer())
            }

        val cameraSelector = CameraSelector.DEFAULT_BACK_CAMERA
        try {
            provider.unbindAll()
            provider.bindToLifecycle(this, cameraSelector, preview, analyzer)
        } catch (e: Exception) {
            e.printStackTrace()
            Toast.makeText(this, "打开相机异常[0]", Toast.LENGTH_LONG).show()
            finish()
            return
        }
    }

    private fun initCxx() {
        CxxEntrance.registerFunctions("UpdateUI") { params ->
            onUpdateUI(params)
            return@registerFunctions ""
        }
    }

    private fun onUpdateUI(params: String?) {
        Log.i("ZHP_TEST", "Cxx 层通知更新 UI 了，params: $params")
    }



}