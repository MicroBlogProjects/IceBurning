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
 * @method get_usernmae
 * @return {String}
 */
get_usernmae : function (
)
{
    return ;
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
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
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
 * @method set_usernmae
 * @param {String} arg0
 */
set_usernmae : function (
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
 * @method get_result
 * @return {int}
 */
get_result : function (
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
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
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
 * @method set_uin
 * @param {int} arg0
 */
set_uin : function (
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
 * @method get_result
 * @return {int}
 */
get_result : function (
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
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
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
 * @method set_rooms
 * @param {Array} arg0
 */
set_rooms : function (
array 
)
{
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
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
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
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
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
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
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
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
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
 * @method get_msgID
 * @return {int}
 */
get_msgID : function (
)
{
    return 0;
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
 * @method set_msgID
 * @param {int} arg0
 */
set_msgID : function (
int 
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
 * @return {GameJoy::JS_CSFightReadyResponse}
 */
Instance : function (
)
{
    return GameJoy::JS_CSFightReadyResponse;
},

};
