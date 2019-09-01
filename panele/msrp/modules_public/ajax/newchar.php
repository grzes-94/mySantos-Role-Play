<?php
if ( ! defined( 'IN_IPB' ) ) exit();

class public_msrp_ajax_newchar extends ipsAjaxCommand 
{
	/**
	 * Class entry point
	 *
	 * @access	public
	 * @param	object		Registry reference
	 * @return	void		[Outputs to screen]
	 */
	
	public function doExecute( ipsRegistry $registry ) 
	{		
		$gender = $this->request['gender']==1?1:2;
		
		$skins = $this->getSkins(true);
		$skins = $skins[$gender];
		
		$returnSkins = '';
		
		foreach($skins as $skin)
		{
			$returnSkins .= '<img src="public/skins/'.$skin.'.png" alt="'.$skin.'" class="skinimg" style="height: 120px;width: 55px;" />';
		}
		
		$this->returnJsonArray(array(
			'skins' => $returnSkins,
		));
	}
	
	static public function getSkins($splitToGender = true)
	{
		$db = ipsRegistry::DB();

		$db->query('SELECT model,sex FROM fc_skins');
		$db->execute();

		$returnList = array();

		if($splitToGender)
		{
			while($row = $db->fetch())
			{
				$returnList[intval($row['sex'])][] = $row['model'];
			}
		}
		else
		{
			while($row = $db->fetch())
			{
				$returnList[] = $row['model'];
			}
		}
		return $returnList;
	}
}
?>