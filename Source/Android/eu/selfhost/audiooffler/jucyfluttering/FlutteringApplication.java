package eu.selfhost.audiooffler.jucyfluttering;

import android.app.Application;
import io.flutter.embedding.engine.FlutterEngine;
import io.flutter.embedding.engine.dart.DartExecutor.DartEntrypoint;
import io.flutter.embedding.engine.FlutterEngineCache;
import com.rmsl.juce.Java;

public class FlutteringApplication extends Application
{
    private FlutterEngine flutterEngine;

    @Override
    public void onCreate()
    {
        super.onCreate();

        Java.initialiseJUCE (this);

        // Instantiate a FlutterEngine.
        flutterEngine = new FlutterEngine(this);
        // Configure an initial route.
        flutterEngine.getNavigationChannel().setInitialRoute("/");
        // Start executing Dart code to pre-warm the FlutterEngine.
        flutterEngine.getDartExecutor().executeDartEntrypoint(DartEntrypoint.createDefault());
        // Cache the FlutterEngine to be used by FlutterActivity.
        FlutterEngineCache.getInstance().put("fluttering_engine_id", flutterEngine);
    }
}
