#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

// Função para criar logs (Aspecto transversal)
void logErro(const string &mensagem) {
    ofstream logFile("log_erros.txt", ios::app);
    if (logFile.is_open()) {
        // Obtendo o horário atual para o log
        time_t now = time(0);
        string dt = ctime(&now);
        dt.pop_back(); // Remove o '\n' da data
        logFile << "[" << dt << "] " << mensagem << endl;
        logFile.close();
    } else {
        cerr << "Erro ao abrir o arquivo de log." << endl;
    }
}

// Classe base para contas bancárias
class ContaBancaria {
protected:
    string titular;
    double saldo;

public:
    ContaBancaria(const string &titular, double saldoInicial)
        : titular(titular), saldo(saldoInicial) {}

    virtual void sacar(double valor) = 0;

    virtual void exibirSaldo() const {
        cout << "Titular: " << titular << " | Saldo: R$ " << saldo << endl;
    }

    virtual ~ContaBancaria() {}
};

// Classe Conta Corrente
class ContaCorrente : public ContaBancaria {
public:
    ContaCorrente(const string &titular, double saldoInicial)
        : ContaBancaria(titular, saldoInicial) {}

    void sacar(double valor) override {
        if (valor > saldo) {
            logErro("Saldo insuficiente na conta corrente de " + titular);
            cout << "Saldo insuficiente na conta corrente." << endl;
        } else {
            saldo -= valor;
            cout << "Saque realizado na conta corrente. Novo saldo: R$ " << saldo << endl;
        }
    }
};

// Classe Conta Poupança
class ContaPoupanca : public ContaBancaria {
public:
    ContaPoupanca(const string &titular, double saldoInicial)
        : ContaBancaria(titular, saldoInicial) {}

    void sacar(double valor) override {
        if (valor > saldo) {
            logErro("Saldo insuficiente na conta poupança de " + titular);
            cout << "Saldo insuficiente na conta poupança." << endl;
        } else {
            saldo -= valor;
            cout << "Saque realizado na conta poupança. Novo saldo: R$ " << saldo << endl;
        }
    }
};

// Classe Conta Investimento
class ContaInvestimento : public ContaBancaria {
public:
    ContaInvestimento(const string &titular, double saldoInicial)
        : ContaBancaria(titular, saldoInicial) {}

    void sacar(double valor) override {
        if (valor > saldo) {
            logErro("Saldo insuficiente na conta investimento de " + titular);
            cout << "Saldo insuficiente na conta investimento." << endl;
        } else {
            saldo -= valor;
            cout << "Saque realizado na conta investimento. Novo saldo: R$ " << saldo << endl;
        }
    }
};

// Função principal
int main() {
    // Criando contas
    ContaCorrente cc("João", 1000.0);
    ContaPoupanca cp("Maria", 500.0);
    ContaInvestimento ci("Carlos", 2000.0);

    // Exibindo os saldos iniciais
    cc.exibirSaldo();
    cp.exibirSaldo();
    ci.exibirSaldo();

    // Realizando saques
    cout << "\n--- Realizando saques ---\n";
    cc.sacar(1200.0); // Saque maior que o saldo (gera log)
    cp.sacar(300.0);  // Saque permitido
    ci.sacar(2500.0); // Saque maior que o saldo (gera log)

    // Exibindo os saldos após os saques
    cout << "\n--- Saldos após os saques ---\n";
    cc.exibirSaldo();
    cp.exibirSaldo();
    ci.exibirSaldo();

    cout << "\nVerifique o arquivo 'log_erros.txt' para os registros de erros.\n";

    return 0;
}
