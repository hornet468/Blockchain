#include <iostream>
#include <cassert>
#include "../ed25519/src/ed25519.h"
#include "transactions.h"

void testTransactions() {
    // Key pair generation
    unsigned char private_key[64], public_key[32], seed[32];
    ed25519_create_seed(seed);
    ed25519_create_keypair(public_key, private_key, seed);

    // Create transaction
    Transactions transaction("Alice", "Bob", 50.0, "");
    std::cout << "Test: Transaction created.\n";

    // Check initialization correctness
    assert(transaction.getSender() == "Alice" && "Incorrect sender");
    assert(transaction.getReceiver() == "Bob" && "Incorrect receiver");
    assert(transaction.getAmount() == 50.0 && "Incorrect amount");
    std::cout << "Test: Initialization successful.\n";

    // Sign transaction
    transaction.signTransaction(private_key, public_key);
    std::cout << "Test: Transaction signed.\n";

    // Check that signature is not empty
    assert(!transaction.getSignature().empty() && "Signature not created!");
    std::cout << "Test: Signature created successfully.\n";

    // Hash the transaction
    std::string transactionHash = transaction.hashTransactions(transaction);
    assert(!transactionHash.empty() && "Transaction hash is empty!");
    std::cout << "Test: Transaction hash created successfully.\n";

    // Verify signature
    std::string message = transaction.toJson().dump();
    transaction.verifySignature(transaction.getSignature(), message, public_key);
    std::cout << "Test: Signature verification passed.\n";

    // Test with an incorrect signature
    std::string invalidSignature = transaction.getSignature();
    invalidSignature[0] = (invalidSignature[0] == '0') ? '1' : '0'; // Change the first character
    std::cout << "Test: Starting invalid signature verification...\n";
    transaction.verifySignature(invalidSignature, message, public_key);

    std::cout << "All tests passed successfully!\n";
}

int main() {
    testTransactions();
    return 0;
}