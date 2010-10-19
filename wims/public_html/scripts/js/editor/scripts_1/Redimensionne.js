
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
  //textDiv.style.height = (y + 5) + 'px';

  //if(element != handleCorner)
    //handleCorner.style.top = y + 'px';

  //handleRight.style.height = y + 'px';

  if(element != handleBottom)
    handleBottom.style.top = y + 'px';
  
  wims_deposit_id.style.height = (y - 19) + 'px';
 
}

function DoWidth(x, element)
{
	var decalage = 2;
  /*textDiv.style.width =  (x + 5) + 'px';*/

  if(element != handleCorner)
    handleCorner.style.left = x + 'px';

  if(element != handleRight)
    handleRight.style.left = x + 'px';

  handleBottom.style.width = x + 'px';
 // handleBottom.style.top = redim_div.style.height + 'px';
  handleBottom.style.top = redim_div.style.height;
//alert(redim_div.style.height);
  redim_div.style.width = (x - decalage) + 'px';
  enev_menu.style.width = (x - decalage) + 'px';
  //enev_menu.style.width = wims_deposit_id.offsetHeight + 'px';
  

}