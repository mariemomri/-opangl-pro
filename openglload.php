<?php
// Paramètres de connexion à la base de données
$host = 'localhost';
$dbname = 'testopengl';
$username = 'root';
$password = '';
try {
    // Connexion à la base de données avec PDO
    $pdo = new PDO("mysql:host=$host;dbname=$dbname", $username, $password);
    // Définir le mode d'erreur
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);


    // Requête pour récupérer les dernières coordonnées
    $sql = "SELECT x, y, z FROM coordinates ORDER BY id DESC LIMIT 1";
    $stmt = $pdo->query($sql);


    // Vérifier si une ligne a été récupérée
    if ($stmt->rowCount() > 0) {
        // Récupérer les données sous forme de tableau associatif
        $row = $stmt->fetch(PDO::FETCH_ASSOC);
        $x = $row['x'];
        $y = $row['y'];
        $z = $row['z'];


        // Retourner les données sous forme de JSON
        echo json_encode(['x' => $x, 'y' => $y, 'z' => $z]);
    } else {
        echo json_encode(['error' => 'Aucune donnée trouvée']);
    }
} catch (PDOException $e) {
    // Gestion des erreurs
    echo json_encode(['error' => 'Erreur de connexion à la base de données : ' . $e->getMessage()]);
}
?>


