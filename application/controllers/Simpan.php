<?php
defined('BASEPATH') OR exit('No direct script access allowed');

class Simpan extends CI_Controller {

	public function index()
	{
		$this->load->view('Home');
	}

  public function store($suhu,$kelembapan){
    $data = array(
    'suhu' => $suhu,
    'kelembapan' => $kelembapan
    );
    $this->db->insert('tbl_sensor', $data);
  }
}
