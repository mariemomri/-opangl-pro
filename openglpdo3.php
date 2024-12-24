<?php
// Paramètres de la base de données
$host = 'localhost';
$dbname = 'testopengl';
$username = 'root';
$password = '';


header('Content-Type: application/json');

try {
    $pdo = new PDO("mysql:host=$host;dbname=$dbname;charset=utf8", $username, $password);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    if ($_SERVER['REQUEST_METHOD'] === 'POST') {
        $translationx = $_POST['translationx'] ?? null;
        $translationy = $_POST['translationy'] ?? null;
        $translationz = $_POST['translationz'] ?? null;
        $rotationx = $_POST['rotationx'] ?? null;
        $rotationy = $_POST['rotationy'] ?? null;
        $rotationz = $_POST['rotationz'] ?? null;
        $scalex = $_POST['scalex'] ?? null;
        $scaley = $_POST['scaley'] ?? null;
        $scalez = $_POST['scalez'] ?? null;

        if ($translationx !== null && $translationy !== null && $translationz !== null) {
            $stmt = $pdo->prepare("INSERT INTO coordinates (translationx, translationy, translationz, rotationx, rotationy, rotationz, scalex, scaley, scalez) VALUES (:translationx, :translationy, :translationz, :rotationx, :rotationy, :rotationz, :scalex, :scaley, :scalez)");
            $stmt->bindParam(':translationx', $translationx);
            $stmt->bindParam(':translationy', $translationy);
            $stmt->bindParam(':translationz', $translationz);
            $stmt->bindParam(':rotationx', $rotationx);
            $stmt->bindParam(':rotationy', $rotationy);
            $stmt->bindParam(':rotationz', $rotationz);
            $stmt->bindParam(':scalex', $scalex);
            $stmt->bindParam(':scaley', $scaley);
            $stmt->bindParam(':scalez', $scalez);
            $stmt->execute();

            echo json_encode(['success' => true, 'message' => 'Coordinates saved successfully.']);
        } else {
            echo json_encode(['success' => false, 'message' => 'Invalid coordinates.']);
        }
    } else {
        echo json_encode(['success' => false, 'message' => 'Unsupported request method.']);
    }
} catch (PDOException $e) {
    echo json_encode(['success' => false, 'message' => 'Error: ' . $e->getMessage()]);
} catch (PDOException $e) {
    echo json_encode(['success' => false, 'message' => 'Erreur : ' . $e->getMessage()]);
}


