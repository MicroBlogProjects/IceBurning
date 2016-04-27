/**
 * @module GameJoy
 */
var GameJoy = GameJoy || {};

/**
 * @class Proxy
 */
GameJoy.Proxy = {

/**
 * @method RecvResponse
 * @return {int}
 */
RecvResponse : function (
)
{
    return 0;
},

/**
 * @method SendRequest
 * @param {int} arg0
 */
SendRequest : function (
int 
)
{
},

};

/**
 * @class JS_CPP_Bridge
 */
GameJoy.JS_CPP_Bridge = {

/**
 * @method JS_CPP_Bridge
 * @constructor
 */
JS_CPP_Bridge : function (
)
{
},

};

/**
 * @class JS_CSLoginRequest
 */
GameJoy.JS_CSLoginRequest = {

/**
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
)
{
},

/**
 * @method set_username
 * @param {String} arg0
 */
set_username : function (
str 
)
{
},

/**
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
},

/**
 * @method get_username
 * @return {String}
 */
get_username : function (
)
{
    return ;
},

/**
 * @method get_password
 * @return {String}
 */
get_password : function (
)
{
    return ;
},

/**
 * @method set_password
 * @param {String} arg0
 */
set_password : function (
str 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSLoginRequest}
 */
Instance : function (
)
{
    return GameJoy::JS_CSLoginRequest;
},

};

/**
 * @class JS_CSLoginResponse
 */
GameJoy.JS_CSLoginResponse = {

/**
 * @method set_uin
 * @param {int} arg0
 */
set_uin : function (
int 
)
{
},

/**
 * @method get_result
 * @return {int}
 */
get_result : function (
)
{
    return 0;
},

/**
 * @method get_uin
 * @return {int}
 */
get_uin : function (
)
{
    return 0;
},

/**
 * @method set_result
 * @param {int} arg0
 */
set_result : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSLoginResponse}
 */
Instance : function (
)
{
    return GameJoy::JS_CSLoginResponse;
},

};

/**
 * @class JS_CSRoomMessage
 */
GameJoy.JS_CSRoomMessage = {

/**
 * @method set_username
 * @param {String} arg0
 */
set_username : function (
str 
)
{
},

/**
 * @method set_uin
 * @param {int} arg0
 */
set_uin : function (
int 
)
{
},

/**
 * @method get_username
 * @return {String}
 */
get_username : function (
)
{
    return ;
},

/**
 * @method get_uin
 * @return {int}
 */
get_uin : function (
)
{
    return 0;
},

/**
 * @method JS_CSRoomMessage
 * @constructor
 */
JS_CSRoomMessage : function (
)
{
},

};

/**
 * @class JS_CSPullRoomsRequest
 */
GameJoy.JS_CSPullRoomsRequest = {

/**
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
},

/**
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSPullRoomsRequest}
 */
Instance : function (
)
{
    return GameJoy::JS_CSPullRoomsRequest;
},

};

/**
 * @class JS_CSPullRoomsResponse
 */
GameJoy.JS_CSPullRoomsResponse = {

/**
 * @method set_rooms
 * @param {Array} arg0
 */
set_rooms : function (
array 
)
{
},

/**
 * @method get_result
 * @return {int}
 */
get_result : function (
)
{
    return 0;
},

/**
 * @method get_rooms
 * @return {Array}
 */
get_rooms : function (
)
{
    return new Array();
},

/**
 * @method set_result
 * @param {int} arg0
 */
set_result : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSPullRoomsResponse}
 */
Instance : function (
)
{
    return GameJoy::JS_CSPullRoomsResponse;
},

};

/**
 * @class JS_CSCreateRoomRequest
 */
GameJoy.JS_CSCreateRoomRequest = {

/**
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
},

/**
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSCreateRoomRequest}
 */
Instance : function (
)
{
    return GameJoy::JS_CSCreateRoomRequest;
},

};

/**
 * @class JS_CSCreateRoomResponse
 */
GameJoy.JS_CSCreateRoomResponse = {

/**
 * @method get_result
 * @return {int}
 */
get_result : function (
)
{
    return 0;
},

/**
 * @method set_result
 * @param {int} arg0
 */
set_result : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSCreateRoomResponse}
 */
Instance : function (
)
{
    return GameJoy::JS_CSCreateRoomResponse;
},

};

/**
 * @class JS_CSJoinRoomRequest
 */
GameJoy.JS_CSJoinRoomRequest = {

/**
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
},

/**
 * @method set_uin
 * @param {int} arg0
 */
set_uin : function (
int 
)
{
},

/**
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
)
{
},

/**
 * @method get_uin
 * @return {int}
 */
get_uin : function (
)
{
    return 0;
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSJoinRoomRequest}
 */
Instance : function (
)
{
    return GameJoy::JS_CSJoinRoomRequest;
},

};

/**
 * @class JS_CSJoinRoomResponse
 */
GameJoy.JS_CSJoinRoomResponse = {

/**
 * @method get_result
 * @return {int}
 */
get_result : function (
)
{
    return 0;
},

/**
 * @method set_result
 * @param {int} arg0
 */
set_result : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSJoinRoomResponse}
 */
Instance : function (
)
{
    return GameJoy::JS_CSJoinRoomResponse;
},

};

/**
 * @class JS_CSFightReadyRequest
 */
GameJoy.JS_CSFightReadyRequest = {

/**
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
},

/**
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSFightReadyRequest}
 */
Instance : function (
)
{
    return GameJoy::JS_CSFightReadyRequest;
},

};

/**
 * @class JS_CSFightReadyResponse
 */
GameJoy.JS_CSFightReadyResponse = {

/**
 * @method get_result
 * @return {int}
 */
get_result : function (
)
{
    return 0;
},

/**
 * @method set_result
 * @param {int} arg0
 */
set_result : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSFightReadyResponse}
 */
Instance : function (
)
{
    return GameJoy::JS_CSFightReadyResponse;
},

};

/**
 * @class JS_PBFrameMessage
 */
GameJoy.JS_PBFrameMessage = {

/**
 * @method get_pos_y
 * @return {int}
 */
get_pos_y : function (
)
{
    return 0;
},

/**
 * @method get_pos_x
 * @return {int}
 */
get_pos_x : function (
)
{
    return 0;
},

/**
 * @method set_pos_y
 * @param {int} arg0
 */
set_pos_y : function (
int 
)
{
},

/**
 * @method set_pos_x
 * @param {int} arg0
 */
set_pos_x : function (
int 
)
{
},

/**
 * @method set_frame
 * @param {int} arg0
 */
set_frame : function (
int 
)
{
},

/**
 * @method get_uin
 * @return {int}
 */
get_uin : function (
)
{
    return 0;
},

/**
 * @method set_type
 * @param {int} arg0
 */
set_type : function (
int 
)
{
},

/**
 * @method get_obj_id
 * @return {int}
 */
get_obj_id : function (
)
{
    return 0;
},

/**
 * @method get_type
 * @return {int}
 */
get_type : function (
)
{
    return 0;
},

/**
 * @method set_obj_id
 * @param {int} arg0
 */
set_obj_id : function (
int 
)
{
},

/**
 * @method set_uin
 * @param {int} arg0
 */
set_uin : function (
int 
)
{
},

/**
 * @method get_frame
 * @return {int}
 */
get_frame : function (
)
{
    return 0;
},

/**
 * @method JS_PBFrameMessage
 * @constructor
 */
JS_PBFrameMessage : function (
)
{
},

};

/**
 * @class JS_CSFrameSyncRequest
 */
GameJoy.JS_CSFrameSyncRequest = {

/**
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
},

/**
 * @method get_step
 * @return {GameJoy::JS_PBFrameMessage}
 */
get_step : function (
)
{
    return GameJoy::JS_PBFrameMessage;
},

/**
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
)
{
},

/**
 * @method set_step
 * @param {GameJoy::JS_PBFrameMessage} arg0
 */
set_step : function (
js_pbframemessage 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSFrameSyncRequest}
 */
Instance : function (
)
{
    return GameJoy::JS_CSFrameSyncRequest;
},

};

/**
 * @class JS_CSFrameSyncResponse
 */
GameJoy.JS_CSFrameSyncResponse = {

/**
 * @method get_steps
 * @return {Array}
 */
get_steps : function (
)
{
    return new Array();
},

/**
 * @method get_result
 * @return {int}
 */
get_result : function (
)
{
    return 0;
},

/**
 * @method set_steps
 * @param {Array} arg0
 */
set_steps : function (
array 
)
{
},

/**
 * @method set_result
 * @param {int} arg0
 */
set_result : function (
int 
)
{
},

/**
 * @method Instance
 * @return {GameJoy::JS_CSFrameSyncResponse}
 */
Instance : function (
)
{
    return GameJoy::JS_CSFrameSyncResponse;
},

};
