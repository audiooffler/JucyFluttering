package eu.selfhost.audiooffler.jucyfluttering;

import io.flutter.embedding.android.FlutterActivity;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.content.Intent;

public class FlutteringActivity extends FlutterActivity // Activity
{
    //==============================================================================
    private static Context m_currentContext = null;

    public static Context getCurrentContext()
    {
        return m_currentContext;
    }

    //==============================================================================

    @Override
    public void onCreate(Bundle savedInstanceState) {
        //com.rmsl.juce.Java.initialiseJUCE(this);
        // keep current context
        m_currentContext = this;
        super.onCreate(savedInstanceState);
    }

    @Override
    protected void onResume()
    {
        // keep current context
        m_currentContext = this;
        super.onResume();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    //==============================================================================
    private native void appNewIntent (Intent intent);

    @Override
    protected void onNewIntent (Intent intent)
    {
        super.onNewIntent(intent);
        setIntent(intent);

        appNewIntent (intent);
    }
}