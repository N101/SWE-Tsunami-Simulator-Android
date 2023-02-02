package com.example.cppdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;


public class HomeScreen extends AppCompatActivity {

    public void computeWaveSpeeds(View view) {
        Intent intent = new Intent(this, WaveSpeed.class);
        startActivity(intent);
    }

    public void SWE1D(View view) {
        Intent intent = new Intent(this, SWE1D.class);
        startActivity(intent);
    }

    public void SWE(View view) {
        Intent intent = new Intent(this, SWE.class);
        startActivity(intent);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_screen);

        setTitle("Home Screen");
        ImageView imageView = (ImageView) findViewById(R.id.imageView);
        imageView.setImageResource(R.drawable.the_great_wave_off_kanagawa_7107112_1280);
        
    }
}