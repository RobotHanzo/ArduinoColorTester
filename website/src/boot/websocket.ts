import {boot} from 'quasar/wrappers'
import {Dialog, Loading} from 'quasar';
import {BoardInfo, ScanResult} from 'boot/api/api';
import {App, reactive, ref} from 'vue';
import ExcelJs from 'exceljs';

// "async" is optional;
// more info on params: https://v2.quasar.dev/quasar-cli/boot-files
let ws: WebSocket;
let arduinoBoardInfo: BoardInfo;
let esp32BoardInfo: BoardInfo;

function connect(app: App, firstTime: boolean) {
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
      case WebSocketEventCodes.REPLY_LIST_SCAN_RESULTS.valueOf(): {
        app.config.globalProperties.$scanResultNames.value = data.data.names;
        break;
      }
      case WebSocketEventCodes.SCAN_FINISHED.valueOf(): {
        ws.send(JSON.stringify({
          eventCode: WebSocketEventCodes.LIST_SCAN_RESULTS.valueOf()
        }))
        break;
      }
      case WebSocketEventCodes.REPLY_READ_SCAN_RESULT.valueOf(): {
        const rows: number[][] = [];
        for (const x of data.data.data as ScanResult[]) {
          rows.push([
            x.profile.brightness, x.profile.scanInterval, x.profile.scanTimes,
            x.brief.medianR, x.brief.medianG, x.brief.medianB,
            x.brief.averageR, x.brief.averageG, x.brief.averageB,
          ])
        }
        const workbook = new ExcelJs.Workbook();
        const sheet = workbook.addWorksheet('Results');
        sheet.addTable({
          name: 'results',
          ref: 'A1',
          columns: [{name: 'Brightness'}, {name: 'Scan Interval'}, {name: 'Scan Times'},
            {name: 'Median of R'}, {name: 'Median of G'}, {name: 'Median of B'},
            {name: 'Average of R'}, {name: 'Average of G'}, {name: 'Average of B'},],
          rows: rows
        });
        workbook.xlsx.writeBuffer().then((content) => {
          const link = document.createElement('a');
          const blobData = new Blob([content], {
            type: 'application/vnd.ms-excel;charset=utf-8;'
          });
          link.download = data.data.name + '.xlsx';
          link.href = URL.createObjectURL(blobData);
          link.click();
        });
        break;
      }
      case WebSocketEventCodes.REPLY_QUERY_SCAN_PROGRESS.valueOf(): {
        Object.assign(app.config.globalProperties.$scanProgress, data.data);
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
        connect(app, false);
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
  SCHEDULE_SCAN = 100,
  QUERY_SCAN_PROGRESS = 101,
  READ_SCAN_RESULT = 102,
  SCAN_FINISHED = 103,
  LIST_SCAN_RESULTS = 104,
  DEBUG_SET_LED_BRIGHTNESS = 200,
  DEBUG_READ_PHOTO_RESISTOR = 201,
  DEBUG_ARDUINO_INCOMING_MESSAGE = 202,
  DEBUG_READ_BOARD_INFO = 203,
  REPLY_QUERY_SCAN_PROGRESS = 1101,
  REPLY_READ_SCAN_RESULT = 1102,
  REPLY_LIST_SCAN_RESULTS = 1104,
  REPLY_DEBUG_READ_BOARD_INFO = 1203,
  REPLY_DEBUG_READ_PHOTO_RESISTOR = 1201,
}

export default boot(async ({app}) => {
  connect(app, true);
  app.config.globalProperties.$ws = ws;
  app.config.globalProperties.$scanResultNames = ref([]);
  app.config.globalProperties.$scanProgress = reactive({});
  // updateBoardInfo();
})
export {ws, esp32BoardInfo, arduinoBoardInfo};
