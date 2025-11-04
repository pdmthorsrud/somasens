import os
import json
import websocket
from dotenv import load_dotenv
from haptic_controller import all_vibrate, left_to_right, right_to_left

def interpret_notification(notification_type: str, title: str, body: str) -> list:
    """
    Interpret a notification and return a haptic pattern.
    Currently, all notifications are encoded as an all_vibrate pattern.
    """
    # For now, we'll use all_vibrate for all notifications
    # This can be expanded later to use different patterns based on notification type
    num_motors = 4  # Assuming 4 motors as per haptic_hal.ino
    return all_vibrate(num_motors, intensity=1.0, duration=1)

def on_message(ws, message):
    try:
        data = json.loads(message)
        if data.get('type') == 'push':
            push = data.get('push', {})
            notification_type = push.get('type', 'unknown')
            title = push.get('title', 'No title')
            body = push.get('body', 'No body')
            
            # Get the pattern for this notification
            pattern = interpret_notification(notification_type, title, body)
            
            print(f"\nNew {notification_type} notification:")
            print(f"Title: {title}")
            print(f"Body: {body}")
            print(f"Haptic Pattern: all_vibrate")
            print(f"Pattern Command: {pattern}")
            print("-" * 50)
            
            return pattern
            
    except json.JSONDecodeError:
        print("Received non-JSON message")
        return None

def on_error(ws, error):
    print(f"Error: {error}")

def on_close(ws, close_status_code, close_msg):
    print("WebSocket connection closed")

def on_open(ws):
    print("WebSocket connection established")

def main():
    # Load environment variables
    load_dotenv()
    api_key = os.getenv('pushbullet_api_key')
    
    if not api_key:
        print("Error: PUSHBULLET_API_KEY not found in .env file")
        return
    
    # WebSocket URL
    websocket_url = f"wss://stream.pushbullet.com/websocket/{api_key}"
    
    # Create WebSocket connection
    ws = websocket.WebSocketApp(
        websocket_url,
        on_message=on_message,
        on_error=on_error,
        on_close=on_close,
        on_open=on_open
    )
    
    # Run forever
    ws.run_forever()

if __name__ == "__main__":
    main() 