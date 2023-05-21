import {boot} from 'quasar/wrappers'
import {Dialog, Loading} from 'quasar';
import {BoardInfo} from 'boot/api/api';

// "async" is optional;
// more info on params: https://v2.quasar.dev/quasar-cli/boot-files
let ws: WebSocket;
let arduinoBoardInfo: BoardInfo;
let esp32BoardInfo: BoardInfo;

function connect(firstTime: boolean) {
  console.log(firstTime ? 'Connecting to websocket...' : 'Attempting to reconnect to websocket...');
  Loading.show({
    message: firstTime ? 'Connecting to the server...' : 'Attempting to reconnect to the server...',
  });
  ws = new WebSocket('ws://192.168.4.1/ws');
  ws.onopen = function () {
    Loading.hide();
    console.log('WebSocket Client Connected');
  };

  ws.onmessage = function (e) {
    const data: WebSocketEvent = JSON.parse(e.data);
    switch (data.eventCode) {
      case WebSocketEventCodes.ACK.valueOf(): {
        break;
      }
      case WebSocketEventCodes.INVALID_MESSAGE.valueOf(): {
        console.error('Message rejected by the server', data);
        break;
      }
      case WebSocketEventCodes.INVALID_EVENT_CODE.valueOf(): {
        console.error('Event code rejected by the server', data);
        break;
      }
      case WebSocketEventCodes.INVALID_DATA.valueOf(): {
        console.error('Data rejected by the server', data);
        break;
      }
      case WebSocketEventCodes.HELLO.valueOf(): {
        console.log('Server says hello');
        break;
      }
      case WebSocketEventCodes.DEBUG_ARDUINO_INCOMING_MESSAGE.valueOf(): {
        break;
      }
      case WebSocketEventCodes.REPLY_DEBUG_READ_BOARD_INFO.valueOf(): {
        arduinoBoardInfo = data.data.arduino;
        esp32BoardInfo = data.data.esp32;
        break;
      }
      default: {
        console.error('Unknown event code', data);
        break;
      }
    }
  };

  ws.onclose = function (e) {
    Loading.show({
      message: 'Connection to the server is lost. Attempting to reconnect...',
    });
    console.log('Socket is closed. Reconnect will be attempted in 1 second.', e.reason);
    setTimeout(function () {
      try {
        connect(false);
      } catch (e) {
        console.error('Failed to reconnect to the server.', e);
        Dialog.create({
          title: 'Failed to reconnect to the server',
          message: 'Please check your internet connection and reload this page.',
          ok: 'Reload',
          persistent: true,
          cancel: false,
        }).onOk(() => {
          location.reload();
        });
      }
    }, 1000);
  };

  ws.onerror = function () {
    console.error('Socket encountered error, closing');
    ws.close();
  };
}

function updateBoardInfo() {
  setTimeout(() => {
    ws.send(JSON.stringify({
      eventCode: WebSocketEventCodes.DEBUG_READ_BOARD_INFO,
    }));
    updateBoardInfo();
  }, 1000);
}

/**
 * The base of all websocket events
 * @export
 * @interface WebSocketEvent
 */
export interface WebSocketEvent {
  /**
   *
   * @type {number}
   * @memberof WebSocketEvent
   */
  'eventCode'?: number;
  /**
   *
   * @type {any}
   * @memberof WebSocketEvent
   */
  'data'?: any;
}

export enum WebSocketEventCodes {
  ACK = 0,
  INVALID_MESSAGE = 1,
  INVALID_EVENT_CODE = 2,
  INVALID_DATA = 3,
  HELLO = 10,
  DEBUG_SET_LED_BRIGHTNESS = 200,
  DEBUG_READ_PHOTO_RESISTOR = 201,
  DEBUG_ARDUINO_INCOMING_MESSAGE = 202,
  DEBUG_READ_BOARD_INFO = 203,
  REPLY_DEBUG_READ_BOARD_INFO = 1203,
  REPLY_DEBUG_READ_PHOTO_RESISTOR = 1201,
}

export default boot(async ({app}) => {
  connect(true);
  app.config.globalProperties.$ws = ws;
  updateBoardInfo();
})
export {ws, esp32BoardInfo, arduinoBoardInfo};
