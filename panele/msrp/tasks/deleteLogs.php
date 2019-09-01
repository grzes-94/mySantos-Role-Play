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

		$query = $this->DB->query("SELECT `player_uid`,`global_id`,`online_today` FROM `srv_characters` WHERE `admin` > 0 ");
		
		while ( $row= $query->fetch_assoc())
		{
			$q2 = sprintf("INSERT INTO `panel_admins_online` VALUES (NULL, %d, %d, %d, NOW())",$row['player_uid'], $row['global_id'], $row['online_today']);
			$this->DB->query($q2);
			
			DELETE FROM `srv_cash_logs` WHERE `time` < UNIX_TIMESTAMP() - (30*24*3600)


		}

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
