

//test return call js funtion from object c and get return value
function test1()
{   
    print("this is test 1,check NSLog output you will recieve a result");
    return "return from test1";
}

//test call execObjectC from JavaScript
function test2()
{
    var ret = callObjc("test2");
    print (ret);
    return ret;
}
//test 3 call execObjectC in Object C directly
//print(callObjc('call callObjc directly'));

//test JS exception
function test4()
{
    var ret = fakefuntion("test4");
    return ret;
}


function start()
{
    print("Hello, This is JSC Test Case");
}

start();


