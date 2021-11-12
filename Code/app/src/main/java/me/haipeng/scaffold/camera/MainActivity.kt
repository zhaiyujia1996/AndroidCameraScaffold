package me.haipeng.scaffold.camera

import android.Manifest
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import androidx.core.app.ActivityCompat
import androidx.core.content.PermissionChecker.PERMISSION_GRANTED

class MainActivity : AppCompatActivity() {

    /* ======================================================= */
    /* Fields                                                  */
    /* ======================================================= */

    /**
     * 打开相机按钮
     */
    private lateinit var openCameraButton: Button

    /**
     * 危险权限校验列表，按照权限组进行校验即可
     */
    private val permissions = listOf(
        // 相机权限
        Manifest.permission.CAMERA
    )



    /* ======================================================= */
    /* Override/Implements Methods                             */
    /* ======================================================= */

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        openCameraButton = findViewById(R.id.openCamera)
        openCameraButton.setOnClickListener {
            if (checkPermissions()) {
                startActivity(Intent(this, CameraActivity::class.java))
            }
        }
    }




    /* ======================================================= */
    /* Private Methods                                         */
    /* ======================================================= */

    private fun checkPermissions(): Boolean {
        var allGranted = true
        permissions.forEach {
            val has = hasPermission(it)
            if (!has) {
                allGranted = false
                ActivityCompat.requestPermissions(this, arrayOf(it), 1)
            }
        }

        return allGranted
    }

    private fun hasPermission(permission: String): Boolean {
        return ActivityCompat.checkSelfPermission(this, permission) == PERMISSION_GRANTED
    }

}