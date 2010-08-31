
var wims_deposit = document.getElementById("wims_deposit");
var handleRight = document.getElementById("handleRight");
var handleCorner = document.getElementById("handleCorner");
var handleBottom = document.getElementById("handleBottom");
var textDiv = document.getElementById("textDiv");

new dragObject(handleRight, null, new Position(15, 0), new Position(800, 0), null, RightMove, null, false);
new dragObject(handleBottom, null, new Position(0, 15), new Position(0, 500), null, BottomMove, null, false);
new dragObject(handleCorner, null, new Position(15, 15), new Position(800, 800), null, CornerMove, null, false);

function BottomMove(newPos, element)
{
  DoHeight(newPos.Y, element);
}

function RightMove(newPos, element)
{
  DoWidth(newPos.X, element);
}

function CornerMove(newPos, element)
{
  DoHeight(newPos.Y, element);
  DoWidth(newPos.X, element);
}

function DoHeight(y, element)
{
  textDiv.style.height = (y + 5) + 'px';

  if(element != handleCorner)
    handleCorner.style.top = y + 'px';

  handleRight.style.height = y + 'px';

  if(element != handleBottom)
    handleBottom.style.top = y + 'px';
  
  wims_deposit.style.height = (y - 19) + 'px';
}

function DoWidth(x, element)
{
  textDiv.style.width =  (x + 5) + 'px';

  if(element != handleCorner)
    handleCorner.style.left = x + 'px';

  if(element != handleRight)
    handleRight.style.left = x + 'px';

  handleBottom.style.width = x + 'px';

  wims_deposit.style.width = (x - 5) + 'px';