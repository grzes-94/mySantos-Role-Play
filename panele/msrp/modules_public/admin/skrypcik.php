<?php
class public_msrp_admin_skrypcik extends ipsCommand
{
	public function doExecute( ipsRegistry $registry )
	{
		require_once( IPSLib::getAppDir( 'msrp' ) . '/sources/functions.php' );
		$this->registry->setClass( 'functions', new functions( $registry ) );
		$functions = $this->registry->getClass( 'functions' );

		if(! $functions->IsGruopAdmin($this->memberData['member_group_id'],true))
		{
			$this->registry->output->silentRedirect('index.php');
		}
		$vw= 0;
		$path = "`vw`=3";
		$usun = false;
		$i=0;
    $result = $this->DB->query("SELECT * FROM `srv_objects` WHERE $path");
    echo "new tmp;<br />";
    while($row=$result->fetch_assoc())
    {



      echo "tmp = CreateDynamicObject(".$row['model'].", ".$row['x'].", ".$row['y'].", ".$row['z'].", ".$row['rx'].", ".$row['ry'].", ".$row['rz'].", ".$vw.");<br />";

			if($row['mmat']== 2)
			{
	      $res2=$this->DB->query("SELECT * FROM `srv_mmat_texture` WHERE `object_id`=".$row['uid']);
	      while($mmat=$res2->fetch_assoc())
	      {
	        $mColor= $this->ShiftRGBAToABGR($mmat['materialcolor']);

	        echo "SetDynamicObjectMaterial(tmp, ".$mmat['index'].", ".$mmat['modelid'].", \"".$mmat['txdname']."\", \"".$mmat['texturename']."\", ".$mColor." );<br />";

	        //SetDynamicObjectMaterial(ObjectInfo[index][oObject], index2, modelid, txdname, texturename, ShiftRGBAToABGR(materialcolor));";
	      }
			}
			else if($row['mmat']==1)
			{
	      $res2=$this->DB->query("SELECT * FROM `srv_mmat_text` WHERE `object_id`=".$row['uid']);
	      while($mmat=$res2->fetch_assoc())
	      {
	        $fColor= $this->ShiftRGBAToABGR($mmat['fontcolor']);
	        $bColor=$this->ShiftRGBAToABGR($mmat['backcolor']);

	        echo "SetDynamicObjectMaterialText(tmp, ".$mmat['index'].", \"".$mmat['text']."\", ".$mmat['matsize'].", \"".$mmat['fontface']."\", ".$mmat['fontsize'].", ".$mmat['bold'].",".$fColor.", ".$bColor.", ".$mmat['align'].");<br />";


	      }
			}

			if($usun)
			{
				$this->DB->query("DELETE FROM `srv_mmat_texture` WHERE `object_id`=".$row['uid']);
				$this->DB->query("DELETE FROM `srv_mmat_text` WHERE `object_id`=".$row['uid']);
				$i++;
			}
    }
		if($usun)
			$this->DB->query("DELETE FROM `srv_objects` WHERE $path");

			echo "<br />-------------------------<br />Usunieto $i obiektow";



    //CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA areaid = STREAMER_TAG_AREA -1)

	//$this->registry->output->setTitle('Pojazdy w salonie');
	//$this->registry->output->addNavigation( 'Panel administratora', 'app=msrp&module=admin' );
	//$this->registry->output->addNavigation( 'Salon', 'app=msrp&module=admin&section=salon' );
	//	$this->registry->getClass('output')->sendOutput();
}
protected function ShiftRGBAToABGR($color)
{
  if(strlen($color)==1)
    return $color;
  if($color=="FFFFFFFF")
    return "-1";
  $val="0x".$color;
  return $val;
}

}
?>
