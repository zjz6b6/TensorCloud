<?php

// w sum with pageviews and inc links
$CirrusSearchWP10W = 3;
$wgCirrusSearchPageViewsW = 3;// 0.;//2.5;
$wgCirrusSearchPageViewsK = 8E-6;
$wgCirrusSearchPageViewsA = 0.8;

$wgCirrusSearchIncLinksW = 5.0;// 0.7;
$wgCirrusSearchIncLinksK = 30;
$wgCirrusSearchIncLinksA = 0.7;

// w sum with inc links alone (fallback with non content ns)
$wgCirrusSearchIncLinksAloneW = 7;
$wgCirrusSearchIncLinksAloneK = 30;
$wgCirrusSearchIncLinksAloneA = 0.7;

$wgCirrusSearchRescoreProfiles['relforge'] = [
	'supported_namespaces' => 'all',
	'fallback_profile' => 'relforge_inclinks',
	'rescore' => [
		[
			'window' => 8192,
			'window_size_override' => 'CirrusSearchFunctionRescoreWindowSize',
			'query_weight' => 1.0,
			'rescore_query_weight' => 1.0,
			'score_mode' => 'total',
			'type' => 'function_score',
			'function_chain' => 'wsum_pv_inclinks_wp10'
		],
		[
			'window' => 8192,
			'window_size_override' => 'CirrusSearchFunctionRescoreWindowSize',
			'query_weight' => 1.0,
			'rescore_query_weight' => 1.0,
			'score_mode' => 'multiply',
			'type' => 'function_score',
			'function_chain' => 'optional_chain'
		],
	],
];

$wgCirrusSearchRescoreProfiles['relforge_inclinks'] = [
	'supported_namespaces' => 'all',
	'rescore' => [
		[
			'window' => 8192,
			'window_size_override' => 'CirrusSearchFunctionRescoreWindowSize',
			'query_weight' => 1.0,
			'rescore_query_weight' => 1.0,
			'score_mode' => 'total',
			'type' => 'function_score',
			'function_chain' => 'wsum_inclinks'
		],
		[
			'window' => 8192,
			'window_size_override' => 'CirrusSearchFunctionRescoreWindowSize',
			'query_weight' => 1.0,
			'rescore_query_weight' => 1.0,
			'score_mode' => 'multiply',
			'type' => 'function_score',
			'function_chain' => 'optional_chain'
		],
	],
];

$wgCirrusSearchRescoreFunctionScoreChains['wsum_pv_inclinks_wp10'] = [
	'score_mode' => 'sum',
	'boost_mode' => 'sum',
	'functions' => [
		[
			'type' => 'satu',
			'weight' => [
				'value' => 1.8,
				'config_override' => 'CirrusSearchPageViewsW',
				'uri_param_override' => 'cirrusPageViewsW',
			],
			'params' => [
				'field' => 'popularity_score',
				'k' => [
					'value' => 0.0000007,
					'config_override' => 'CirrusSearchPageViewsK',
					'uri_param_override' => 'cirrusPageViewsK',
				],
				'a' => [
					'value' => 1,
					'config_override' => 'CirrusSearchPageViewsA',
					'uri_param_override' => 'cirrusPageViewsA',
				],
			],
		],
		[
			'type' => 'satu',
			'weight' => [
				'value' => 0.6,
				'config_override' => 'CirrusSearchIncLinksW',
				'uri_param_override' => 'cirrusIncLinksW',
			],
			'params' => [
				'field' => 'incoming_links',
				'k' => [
					'value' => 10,
					'config_override' => 'CirrusSearchIncLinksK',
					'uri_param_override' => 'cirrusIncLinksK',
				],
				'a' => [
					'value' => 1,
					'config_override' => 'CirrusSearchIncLinksA',
					'uri_param_override' => 'cirrusIncLinksA',
				],
			],
		],
		[
			'type' => 'custom_field',
			'weight' => [
				'value' => 0.6,
				'config_override' => 'CirrusSearchWP10W',
				'uri_param_override' => 'cirrusWP10W',
			],
			'params' => [
				'field' => 'wp10',
				'modifier' => 'none',
				'missing' => 0,
			],
		],
	],
];

$wgCirrusSearchRescoreFunctionScoreChains['wsum_inclinks'] = [
	'functions' => [
		[
			'type' => 'satu',
			'params' => [
				'field' => 'incoming_links',
				'weight' => [
					'value' => 1.2,
					'config_override' => 'CirrusSearchIncLinksAloneW',
					'uri_param_override' => 'cirrusIncLinksAloneW',
				],
				'k' => [
					'value' => 10,
					'config_override' => 'CirrusSearchIncLinksAloneK',
					'uri_param_override' => 'cirrusIncLinksAloneK',
				],
				'a' => [
					'value' => 1,
					'config_override' => 'CirrusSearchIncLinksAloneA',
					'uri_param_override' => 'cirrusIncLinksAloneA',
				],
			],
		],
	],
];
