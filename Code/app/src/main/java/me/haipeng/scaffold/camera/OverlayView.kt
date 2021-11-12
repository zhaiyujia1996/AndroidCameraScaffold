@file:Suppress("SpellCheckingInspection")

package me.haipeng.scaffold.camera

import android.annotation.SuppressLint
import android.content.Context
import android.graphics.Bitmap
import android.graphics.Canvas
import android.graphics.Paint
import android.graphics.Rect
import android.util.AttributeSet
import android.view.View

/**
 * @author ZhengHaiPeng
 * @since 2021/11/12 10:17 下午
 */
class OverlayView: View {

    /* ======================================================= */
    /* Fields                                                  */
    /* ======================================================= */


    var bitmap: Bitmap? = null
        set(value) {
            field = value
            if (value == null) {
                bmpRect = null
                return
            }
            bmpRect = Rect(0, 0, value.width, value.height)
        }

    private var bmpRect: Rect? = null

    private var canvasRect: Rect? = null

    private val paint = Paint()


    /* ======================================================= */
    /* Constructors                                            */
    /* ======================================================= */

    constructor(context: Context): super(context)

    constructor(context: Context, attrs: AttributeSet): super(context, attrs)

    constructor(context: Context, attrs: AttributeSet, defStyleAttr: Int): super(context, attrs, defStyleAttr)



    /* ======================================================= */
    /* Override/Implements Methods                             */
    /* ======================================================= */

    override fun onDraw(canvas: Canvas?) {
        super.onDraw(canvas)
        val c = bitmap ?: return
        val bmp = bitmap ?: return
        canvas?.drawBitmap(bmp, bmpRect, canvasRect!!, paint)
    }

    @SuppressLint("DrawAllocation")
    override fun onMeasure(widthMeasureSpec: Int, heightMeasureSpec: Int) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec)
        canvasRect = Rect(0, 0, measuredWidth, measuredHeight)
    }

}