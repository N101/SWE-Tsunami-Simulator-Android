package com.example.cppdemo;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.example.cppdemo.databinding.ActivityMainBinding;
//import com.example.funccall.databinding.ActivityMainBinding;

public class WaveSpeed extends AppCompatActivity {

    // Used to load the 'funccall' library on application startup.
    static {
        System.loadLibrary("tsunamiSim");
    }


    public void start(View view) {
        EditText a = (EditText) findViewById(R.id.e1);
        EditText b = (EditText) findViewById(R.id.e2);
        EditText c = (EditText) findViewById(R.id.e3);
        EditText d = (EditText) findViewById(R.id.e4);
        TextView text = (TextView) findViewById(R.id.textView);
        text.setText("");
        int w, x, y, z;


        if (a.getText().toString().isEmpty() || b.getText().toString().isEmpty() || c.getText().toString().isEmpty() || d.getText().toString().isEmpty()) {
            Toast.makeText(this, "Please fill out all fields with NUMBERS!", Toast.LENGTH_SHORT).show();
        } else {
            w = Integer.parseInt(a.getText().toString());
            x = Integer.parseInt(b.getText().toString());
            y = Integer.parseInt(c.getText().toString());
            z = Integer.parseInt(d.getText().toString());

            text.setText(main(w, x, y, z));
        }


    }

    private ActivityMainBinding binding;

    /// Back button function
    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        this.finish();
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        /// Screen title
        setTitle("Compute Wave Speeds");

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        /// Back button
        ActionBar a = getSupportActionBar();
        assert a != null;
        a.setDisplayHomeAsUpEnabled(true);

    }

    /**
     * A native method that is implemented by the 'funccall' native library,
     * which is packaged with this application.
     */

    public native String main(int a, int b, int c, int d);

}