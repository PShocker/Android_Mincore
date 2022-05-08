package com.shocker.mincore;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.shocker.mincore.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'mincore' library on application startup.
    static {
        System.loadLibrary("mincore");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mincore();
            }
        });
    }

    /**
     * A native method that is implemented by the 'mincore' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native void mincore();
}