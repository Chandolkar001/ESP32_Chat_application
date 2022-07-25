var ws = null;
var name = null;
 
function OpenWebsocket() {
 
    const nameTextElement = document.getElementById("nameText");
 
    name = nameTextElement.value;
    nameTextElement.value = '';
     
    const url = `ws://${location.hostname}/chat`;   
    ws = new WebSocket(url);
 
    ws.onopen = function() {
                 
        document.getElementById("inputText").disabled = false;
        document.getElementById("sendButton").disabled = false;
        document.getElementById("disconnectButton").disabled = false;
        document.getElementById("connectButton").disabled = true;
        document.getElementById("nameText").disabled = true;                    
    };
 
    ws.onclose = function() {
    
        document.getElementById("inputText").disabled = true;
        document.getElementById("sendButton").disabled = true;        
        document.getElementById("disconnectButton").disabled = true; 
        document.getElementById("connectButton").disabled = false;
        document.getElementById("nameText").disabled = false;
 
        document.getElementById("chatDiv").innerHTML = '';  
    };
    
    ws.onmessage = function(event) {
 
           const receivedObj = JSON.parse(event.data);
 
           const newChatEntryElement = document.createElement('div');
           const newTag = document.createElement('span');
           const newMsg = document.createElement('span');               
 
           newTag.textContent = receivedObj.name;
           newMsg.textContent = receivedObj.msg;
 
           newTag.classList.add('chat-tag');
 
           newChatEntryElement.appendChild(newTag);
           newChatEntryElement.appendChild(newMsg);
 
           const chatDiv = document.getElementById("chatDiv");          
           chatDiv.appendChild(newChatEntryElement);
          
    };
 }
 
function CloseWebsocket(){
    ws.close();
}
 
function SendData(){
  
    const inputTextElement = document.getElementById("inputText");
  
    const msg = inputTextElement.value;
    inputTextElement.value = '';
  
    const objToSend = {
        msg: msg,
        name: name
    }
     
    const serializedObj = JSON.stringify(objToSend);
     
    ws.send(serializedObj);
}