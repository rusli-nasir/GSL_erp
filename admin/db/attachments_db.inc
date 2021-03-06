<?php
/**********************************************************************
Copyright (C) Grameen Solutions Ltd.(www.grameensolutions.com)
***********************************************************************/

//----------------------------------------------------------------------------------------

function add_attachment($filterType, $trans_no, $description,
	$filename, $unique_name, $filesize, $filetype)
{
	$date = date2sql(Today());
	$sql = "INSERT INTO ".TB_PREF."attachments (type_no, trans_no, description, filename, unique_name,
		filesize, filetype, tran_date) VALUES (".db_escape($filterType).","
		.db_escape($trans_no).",".db_escape($description).", "
		.db_escape($filename).", ".db_escape($unique_name).", ".db_escape($filesize)
		.", ".db_escape($filetype).", '$date')";
	db_query($sql, "Attachment could not be inserted");		
}
//----------------------------------------------------------------------------------------

function update_attachment($selected_id, $filterType, $trans_no, $description,
	$filename, $unique_name, $filesize, $filetype)
{
	$date = date2sql(Today());
	$sql = "UPDATE ".TB_PREF."attachments SET
		type_no=".db_escape($filterType).",
		trans_no=".db_escape($trans_no).",
		description=".db_escape($description).", ";
	if ($filename != "")
	{
		$sql .= "filename=".db_escape($filename).",
		unique_name=".db_escape($unique_name).",
		filesize=".db_escape($filesize).",
		filetype=".db_escape($filetype).",";
	}	
	$sql .= "tran_date='$date' WHERE id=".db_escape($selected_id);
	db_query($sql, "Attachment could not be updated");		
}

//----------------------------------------------------------------------------------------

function delete_attachment($id)
{
	$sql = "DELETE FROM ".TB_PREF."attachments WHERE id = ".db_escape($id);
	db_query($sql, "Could not delete attachment");
}
//----------------------------------------------------------------------------------------

function get_attached_documents($type)
{
	$sql = "SELECT * FROM ".TB_PREF."attachments WHERE type_no=".db_escape($type)
	." ORDER BY trans_no";
	return db_query($sql, "Could not retrieve attachments");
}

function get_attachment($id)
{
	$sql = "SELECT * FROM ".TB_PREF."attachments WHERE id=".db_escape($id);
	$result = db_query($sql, "Could not retrieve attachments");
	return db_fetch($result);
}

function has_attachment($type, $id)
{
	$sql = "SELECT DISTINCT * FROM ".TB_PREF."attachments WHERE type_no=".db_escape($type)." AND trans_no=".db_escape($id);
	$result = db_query($sql, "Could not retrieve attachments");
	$myrow = db_fetch($result);
	if ($myrow === false)
		return 0;
	else
		return $myrow['id'];
}

function get_sql_for_attached_documents($type)
{
	return "SELECT trans_no, description, filename, filesize, filetype, tran_date, id, type_no FROM ".TB_PREF."attachments WHERE type_no=".db_escape($type)
	." ORDER BY trans_no DESC";
}


?>