package com.example.cppdemo;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemSelectedListener;

import java.io.File;


public class SWE extends AppCompatActivity {

    private String outPut = "";

    static {
        System.loadLibrary("tsunamiSim");
    }

    public void start(View view) {
        Spinner ss = (Spinner) findViewById(R.id.dynamic_spinner);
        EditText a = (EditText) findViewById(R.id.swex);
        EditText b = (EditText) findViewById(R.id.swey);
        EditText c = (EditText) findViewById(R.id.checkpoints);
        EditText d = (EditText) findViewById(R.id.cond);
        EditText e = (EditText) findViewById(R.id.basename_input);
        String dirName = ((EditText) findViewById(R.id.swe_dirname)).getText().toString();

        File swe_dir = new File(Environment.getExternalStorageDirectory() + "/" + dirName);
        swe_dir.mkdirs();

        String scenarioName = ss.getSelectedItem().toString();
        int x, y, cp;
        String cond, baseName;

        if (a.getText().toString().isEmpty() || b.getText().toString().isEmpty() || c.getText().toString().isEmpty() || d.getText().toString().isEmpty()) {
            Toast.makeText(this, "Please fill out all fields correctly!", Toast.LENGTH_SHORT).show();
        } else {
            x = Integer.parseInt(a.getText().toString());
            y = Integer.parseInt(b.getText().toString());
            cp = Integer.parseInt(c.getText().toString());
            cond = d.getText().toString();
            baseName = e.getText().toString();

            outPut += main(scenarioName, x, y, cp, cond, baseName, dirName);

            Intent intent = new Intent(view.getContext(), SWEOutput.class);
            intent.putExtra("swe", outPut);
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
        setContentView(R.layout.activity_swe);
        setTitle("SWE");

        Spinner scenarioSelector = (Spinner) findViewById(R.id.dynamic_spinner);


        String[] items = new String[]{"RadialDamBreakScenario", "ArtificialTsunamiScenario", "BathymetryDamBreakScenario"};

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_dropdown_item_1line, items);

        scenarioSelector.setSelection(0);

        scenarioSelector.setAdapter(adapter);
        scenarioSelector.setOnItemSelectedListener(new OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view,
                                       int position, long id) {
                Log.v("item", (String) parent.getItemAtPosition(position));
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
            /// Back button

        });

        ActionBar a = getSupportActionBar();
        assert a != null;
        a.setDisplayHomeAsUpEnabled(true);

    }

    public native String main(String scenarioName, int x, int y, int cp, String cond, String baseName, String dirName);

}