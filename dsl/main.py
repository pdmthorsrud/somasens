import os
from dotenv import load_dotenv
from haptic_controller import HapticController
from pushbullet_listener import on_message, on_error, on_close, on_open
import websocket
import threading

def main():
    # Load environment variables
    load_dotenv()
    api_key = os.getenv('pushbullet_api_key')
    
    if not api_key:
        print("Error: PUSHBULLET_API_KEY not found in .env file")
        return
    
    # Initialize haptic controller
    try:
        controller = HapticController()
        print("Haptic controller initialized successfully")
    except Exception as e:
        print(f"Error initializing haptic controller: {e}")
        return
    
    # WebSocket URL
    websocket_url = f"wss://stream.pushbullet.com/websocket/{api_key}"
    
    # Create WebSocket connection
    ws = websocket.WebSocketApp(
        websocket_url,
        on_message=lambda ws, msg: handle_message(ws, msg, controller),
        on_error=on_error,
        on_close=on_close,
        on_open=on_open
    )
    
    # Run WebSocket in a separate thread
    ws_thread = threading.Thread(target=ws.run_forever)
    ws_thread.daemon = True
    ws_thread.start()
    
    print("Listening for Pushbullet notifications...")
    print("Press Ctrl+C to exit")
    
    try:
        # Keep the main thread alive
        while True:
            pass
    except KeyboardInterrupt:
        print("\nShutting down...")
        ws.close()
        controller.close()

def handle_message(ws, message, controller):
    """Handle incoming WebSocket messages and run haptic patterns."""
    pattern = on_message(ws, message)
    if pattern:
        try:
            controller.run_pattern(pattern)
        except Exception as e:
            print(f"Error running haptic pattern: {e}")

if __name__ == "__main__":
    main() 