package com.tsunamisim.swe;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.MenuItem;
import android.widget.TextView;

import com.tsunamisim.swe.R;

public class SWEOutput extends AppCompatActivity {

    private String text;

    /// Back button function
    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {
        this.finish();
        return super.onOptionsItemSelected(item);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sweoutput);

        setTitle("SWE Output");
        /// Back button
        ActionBar a = getSupportActionBar();
        assert a != null;
        a.setDisplayHomeAsUpEnabled(true);

        text = getIntent().getStringExtra("swe");

//        String[] textArray;
//        textArray = text.split("\n");
//        text = "";
//
//        for (int i = 0; i < textArray.length; i++) {
//            if (textArray[i].contains("checkpoint")) {
//                textArray[i] = textArray[i].toUpperCase();
//            }
//            text += text == "" ? textArray[i] : textArray[i] + "\n";
//        }

        TextView textView = (TextView) findViewById(R.id.textView5);
        textView.setMovementMethod(new ScrollingMovementMethod());

        textView.setText(text);
    }
}