<?php

if ( ! defined( 'IN_IPB' ) )
{
	print "<h1>Incorrect access</h1>You cannot access this file directly. If you have recently upgraded, make sure you upgraded all the relevant files.";
	exit();
}

/**
 *
 * @class		task_item
 * @brief		Task to optimize database tables daily
 *
 */
class task_item
{
	/**
	 * Object that stores the parent task manager class
	 *
	 * @var		$class
	 */
	protected $class;

	/**
	 * Array that stores the task data
	 *
	 * @var		$task
	 */
	protected $task = array();

	/**
	 * Registry Object Shortcuts
	 *
	 * @var		$registry
	 * @var		$DB
	 * @var		$lang
	 */
	protected $registry;
	protected $DB;
	protected $lang;

	/**
	 * Constructor
	 *
	 * @param	object		$registry		Registry object
	 * @param	object		$class			Task manager class object
	 * @param	array		$task			Array with the task data
	 * @return	@e void
	 */
	public function __construct( ipsRegistry $registry, $class, $task )
	{
		/* Make registry objects */
		$this->registry	= $registry;
		$this->DB		= $this->registry->DB();
		$this->lang		= $this->registry->getClass('class_localization');

		$this->class	= $class;
		$this->task		= $task;
	}

	/**
	 * Run this task
	 *
	 * @return	@e void
	 */
	public function runTask()
	{
		//-----------------------------------------
		// Do it
		//-----------------------------------------

		$this->DB->build( array(
			'select'	=> '*',
			'from'		=> 'members',
			'where'		=> 'member_group_id = 9 AND premium<' . time(),
			'order'		=> 'premium ASC',
			) );
		$e = $this->DB->execute();
		while ( $r = $this->DB->fetch( $e ) )
		{
      $id = $r['member_id'];
			$this->DB->query("UPDATE `members` SET `member_group_id` = 3 WHERE `member_id` = $id");

		}
		$this->DB->allow_sub_select=1;
		$this->DB->query("UPDATE `srv_characters` SET `hide`=0 WHERE `hide`=1 AND `global_id` IN (SELECT `member_id` FROM `members` WHERE `premium` < ".(time()-604800).")");
		$this->DB->allow_sub_select=0;

		//-----------------------------------------
		// Finish
		//-----------------------------------------

		/* Log to log table - modify but dont delete */
		$this->registry->getClass('class_localization')->loadLanguageFile( array( 'public_global' ), 'core' );
		$this->class->appendTaskLog( $this->task, $this->lang->words['task__warnings'] );

		/* Unlock Task: DO NOT MODIFY! */
		$this->class->unlockTask( $this->task );
	}
}
