package com.tsunamisim.swe;

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
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemSelectedListener;

import com.tsunamisim.swe.R;

import java.io.File;


public class SWE extends AppCompatActivity {

    static {
        System.loadLibrary("tsunamiSim");
    }

    public void start(View view) {
        Spinner ss = findViewById(R.id.swe_scenario_spinner);
        EditText a = findViewById(R.id.swex);
        EditText b = findViewById(R.id.swey);
        EditText c = findViewById(R.id.checkpoints);
        EditText d = findViewById(R.id.cond);
        EditText e = findViewById(R.id.basename_input);
        EditText time = findViewById(R.id.endTime);
        String dirName = ((EditText) findViewById(R.id.swe_dirname)).getText().toString();

        File swe_dir = new File(Environment.getExternalStorageDirectory() + "/" + dirName);
        swe_dir.mkdirs();

        String scenarioName = ss.getSelectedItem().toString();
        int x, y, cp, t;
        String cond, baseName;

        if (a.getText().toString().isEmpty() || b.getText().toString().isEmpty() || c.getText().toString().isEmpty() || d.getText().toString().isEmpty() || e.getText().toString().isEmpty() || time.getText().toString().isEmpty()) {
            Toast.makeText(this, "Please fill out all fields correctly!", Toast.LENGTH_SHORT).show();
        } else {
            x = Integer.parseInt(a.getText().toString());
            y = Integer.parseInt(b.getText().toString());
            cp = Integer.parseInt(c.getText().toString());
            cond = d.getText().toString();
            baseName = e.getText().toString();
            t = Integer.parseInt(time.getText().toString());

            String outPut = main(scenarioName, x, y, cp, t, cond, baseName, dirName);

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

        Spinner scenarioSelector = findViewById(R.id.swe_scenario_spinner);
        String[] items = new String[]{"RadialDamBreakScenario", "ArtificialTsunamiScenario", "BathymetryDamBreakScenario"};
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_dropdown_item_1line, items);

        scenarioSelector.setSelection(0);
        scenarioSelector.setAdapter(adapter);
        scenarioSelector.setOnItemSelectedListener(new OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                ((TextView) parent.getChildAt(0)).setTextSize(19);
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

    public native String main(String scenarioName, int x, int y, int cp, int end_time, String cond, String baseName, String dirName);

}