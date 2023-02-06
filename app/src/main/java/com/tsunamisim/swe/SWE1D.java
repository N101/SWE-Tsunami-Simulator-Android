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

import com.tsunamisim.swe.R;

import java.io.File;

public class SWE1D extends AppCompatActivity {

    static {
        System.loadLibrary("tsunamiSim");
    }

    public void start(View view) {
        Spinner ss = (Spinner) findViewById(R.id.swe1d_scenario_spinner);
        EditText a = (EditText) findViewById(R.id.swe1size);
        EditText b = (EditText) findViewById(R.id.swe1dtime);
        String dirName = ((EditText) findViewById(R.id.swe1d_dirname)).getText().toString();
        int size, time;
        String scenarioName = ss.getSelectedItem().toString();
        File swe1d_dir = new File(Environment.getExternalStorageDirectory() + "/" + dirName);
        swe1d_dir.mkdirs();

        if (a.getText().toString().isEmpty() || b.getText().toString().isEmpty()) {
            Toast.makeText(this, "Please fill out all fields correctly!", Toast.LENGTH_SHORT).show();
        } else {
            size = Integer.parseInt(a.getText().toString());
            time = Integer.parseInt(b.getText().toString());
            String outPut = main(scenarioName, size, time, dirName);

            Intent intent = new Intent(view.getContext(), SWE1DOutput.class);
            //clear previous text output

            intent.putExtra("swe1dOutput", outPut);
            startActivity(intent);
        }

    }
    //todo rename cppdemo


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

        Spinner scenarioSelector = (Spinner) findViewById(R.id.swe1d_scenario_spinner);
        String[] items = new String[]{
                "DamBreakScenario",
                "ShockShockScenario",
                "RareRareScenario",
                "SubcriticalScenario",
                "SupercriticalScenario"
        };
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_dropdown_item_1line, items);

        scenarioSelector.setSelection(0);
        scenarioSelector.setAdapter(adapter);
        scenarioSelector.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view,
                                       int position, long id) {
                //((TextView) parent.getChildAt(0)).setTextColor(Color.BLUE);
                ((TextView) parent.getChildAt(0)).setTextSize(19);
                Log.v("item", (String) parent.getItemAtPosition(position));
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
            /// Back button

        });

        /// Back button
        ActionBar a = getSupportActionBar();
        assert a != null;
        a.setDisplayHomeAsUpEnabled(true);
    }

    public native String main(String scenarioName, int x, int time_step, String dirName);
}