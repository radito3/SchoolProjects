var myApp = angular.module('myApp');

myApp.controller('GenresController', ['$scope', '$http',
	'$location', '$routeParams', function($scope, $http, $location, $routeParams) {

	$scope.getGenres = function() {
		$http.get('/api/genres').success(function(response) {
			$scope.genres = response;
		});
	}

	$scope.getGenre = function() {
		var id = $routeParams.id;
		$http.get('/api/genre/' + id).success(function(response) {
			$scope.genre = response;
		});
	}

	$scope.addGenre = function() {
		console.log($scope.genre);
		$http.post('/api/genres/', $scope.genre).success(function(response) {
			window.location.href = '#';
		});
	}

	$scope.updateGenre = function() {
		var id = $routeParams.id;
		$http.put('/api/genres/' + id, $scope.genre).success(function(response) {
			window.location.href = '#';
		});
	}

	$scope.removeGenre = function(id) {
		$http.delete('/api/genres/' + id).success(function(response) {
			window.location.href = '#';
		});
	}
}]);
