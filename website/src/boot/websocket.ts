import {boot} from 'quasar/wrappers'

// "async" is optional;
// more info on params: https://v2.quasar.dev/quasar-cli/boot-files
const ws = new WebSocket('ws://192.168.4.1/ws')
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
     * @type {never}
     * @memberof WebSocketEvent
     */
    'data'?: never;
}
export enum WebSocketEventCodes {
    ACK = 0,
    INVALID_MESSAGE = 1,
    INVALID_EVENT_CODE = 2,
    INVALID_DATA = 3,
    HELLO = 10,
    DEBUG_SET_LED_BRIGHTNESS = 200,
    DEBUG_READ_PHOTO_RESISTOR = 201,
    DEBUG_ARDUINO_INCOMING_MESSAGE = 202
};
export default boot(async ({app}) => {
    app.config.globalProperties.$ws = ws;
})
export {ws};
