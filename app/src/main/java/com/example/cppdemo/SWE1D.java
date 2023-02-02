package com.example.cppdemo;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

public class SWE1D extends AppCompatActivity {

    private String outPut = "";

    static {
        System.loadLibrary("cppdemo");
    }
    public void start(View view) {
        EditText a = (EditText) findViewById(R.id.swe1size);
        EditText b = (EditText) findViewById(R.id.swe1dtime);
        String dirName = "swe1d_dir";
        int size, time;
        File swe1d_dir = new File(Environment.getExternalStorageDirectory() + "/" + dirName);
        swe1d_dir.mkdirs();

        if (a.getText().toString().isEmpty() || b.getText().toString().isEmpty()) {
            Toast.makeText(this, "Please fill out all fields correctly!", Toast.LENGTH_SHORT).show();
        } else {
            size = Integer.parseInt(a.getText().toString());
            time = Integer.parseInt(b.getText().toString());

            outPut+= main(size, time, dirName);
            //outPut = "testing";

            Intent intent = new Intent(view.getContext(), SWE1DOutput.class);
            intent.putExtra("swe1d", outPut);
            startActivity(intent);
        }

    }


    /// Back button function
    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        this.finish();
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.acticity_swe1d);
        setTitle("SWE1D");

        /// Back button
        ActionBar a = getSupportActionBar();
        assert a != null;
        a.setDisplayHomeAsUpEnabled(true);
    }

    public native String main(int x, int time_step, String dirName);
}