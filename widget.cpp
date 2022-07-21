#include "widget.h"
#include "./ui_widget.h"

#include <QPalette>
#include <QProcess>
#include <QDir>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    divider = "<font color='grey'>|</font>";
    colorOrange = "#f5a569";
    colorRed = "#fb5e56";
    colorGreen = "#9fdc78";
    colorBlue = "#4ec2e5";
    colorPurple = "#e663a1";

    padASN = 24;
    padISO = 3;
    padCOUNTRY = 15;
    padURLHAUS = 20;
    padTHREATFOX = 20;
    padTOR = 10;

    ui->txt_searchfield->setCursorWidth(2);
    ui->txt_about->setCursorWidth(0);
    ui->txt_about->setText(
                "<body style='white-space: pre-wrap; font-weight: normal;'><img src=':logo.svg' style='float:left;' >"
                "<b style=color:"+ colorOrange +";>IP Lookup v1.0</b><br>"
                "Copyright (C) 2022 Alexander Hübert<br>"
                "Licence: LGPL<br>"
                "contact@huebicode.com<br><br><br>"
                "This is free software. It is provided “as-is” without warranty of any kind.<br><br>"
                "It is using the lite databases of DB-IP <span style=color:"+ colorOrange +";>https://db-ip.com</span> and the free APIs of abuse.ch <span style=color:"+ colorOrange +";>https://abuse.ch</span> (CC0) and the Tor Project, Inc. <span style=color:"+ colorOrange +";>https://torproject.org</span> (CC0).<br><br>"
                "For current results the TOR-Data should be refreshed and the IP databases updated. The databases (ASN lite and Country lite) can be downloaded for free from DB-IP and replaced in the application folder in the \"mmdb\" directory.<br><br>"
                "Shortcuts:<br><br>"
                "     Ctrl + Return: start search<br><br><br>"
                "- made with <span style=color:"+ colorOrange +";>❤️</span> and Qt -<br><br><br><br>"
                "--- USED SOFTWARE, LIBRARIES, DATABASES ---<br><br>"
                "<b style=color:"+ colorOrange +";>Qt Framework v6.3</b><br>"
                "Copyright (C) 2008 - 2022 The Qt Company Ltd. All rights reserved.<br>"
                "License: LGPL<br><br><br>"
                "<b style=color:"+ colorOrange +";>mmdbinspect v0.1.1</b><br>"
                "This software is Copyright (c) 2019 - 2021 by MaxMind, Inc.<br>"
                "This is free software, licensed under the MIT License.<br><br><br>"
                "<b style=color:"+ colorOrange +";>DB-IP Lite Databases</b><br>"
                "IP to ASN lite DB and IP to Country lite DB<br>"
                "The free DB-IP Lite database by DB-IP &lt;https://db-ip.com/&gt; is licensed under a Creative Commons Attribution 4.0 International License.<br><br><br>"
                "--- LICENSES ---<br><br>"
                "<b style=color:"+ colorOrange +";>GNU LESSER GENERAL PUBLIC LICENSE</b><br>"
                "Version 3, 29 June 2007<br>"
                "Copyright © 2007 Free Software Foundation, Inc. &lt;https://fsf.org/&gt;<br><br>"
                "Everyone is permitted to copy and distribute verbatim copies of this license document, but changing it is not allowed.<br><br>"
                "This version of the GNU Lesser General Public License incorporates the terms and conditions of version 3 of the GNU General Public License, supplemented by the additional permissions listed below.<br><br>"
                "0. Additional Definitions.<br>"
                "As used herein, “this License” refers to version 3 of the GNU Lesser General Public License, and the “GNU GPL” refers to version 3 of the GNU General Public License.<br><br>"
                "“The Library” refers to a covered work governed by this License, other than an Application or a Combined Work as defined below.<br><br>"
                "An “Application” is any work that makes use of an interface provided by the Library, but which is not otherwise based on the Library. Defining a subclass of a class defined by the Library is deemed a mode of using an interface provided by the Library.<br><br>"
                "A “Combined Work” is a work produced by combining or linking an Application with the Library. The particular version of the Library with which the Combined Work was made is also called the “Linked Version”.<br><br>"
                "The “Minimal Corresponding Source” for a Combined Work means the Corresponding Source for the Combined Work, excluding any source code for portions of the Combined Work that, considered in isolation, are based on the Application, and not on the Linked Version.<br><br>"
                "The “Corresponding Application Code” for a Combined Work means the object code and/or source code for the Application, including any data and utility programs needed for reproducing the Combined Work from the Application, but excluding the System Libraries of the Combined Work.<br><br>"
                "1. Exception to Section 3 of the GNU GPL.<br>"
                "You may convey a covered work under sections 3 and 4 of this License without being bound by section 3 of the GNU GPL.<br><br>"
                "2. Conveying Modified Versions.<br>"
                "If you modify a copy of the Library, and, in your modifications, a facility refers to a function or data to be supplied by an Application that uses the facility (other than as an argument passed when the facility is invoked), then you may convey a copy of the modified version:<br><br>"
                "a) under this License, provided that you make a good faith effort to ensure that, in the event an Application does not supply the function or data, the facility still operates, and performs whatever part of its purpose remains meaningful, or<br>"
                "b) under the GNU GPL, with none of the additional permissions of this License applicable to that copy.<br><br>"
                "3. Object Code Incorporating Material from Library Header Files.<br>"
                "The object code form of an Application may incorporate material from a header file that is part of the Library. You may convey such object code under terms of your choice, provided that, if the incorporated material is not limited to numerical parameters, data structure layouts and accessors, or small macros, inline functions and templates (ten or fewer lines in length), you do both of the following:<br><br>"
                "a) Give prominent notice with each copy of the object code that the Library is used in it and that the Library and its use are covered by this License.<br>"
                "b) Accompany the object code with a copy of the GNU GPL and this license document.<br><br>"
                "4. Combined Works.<br>"
                "You may convey a Combined Work under terms of your choice that, taken together, effectively do not restrict modification of the portions of the Library contained in the Combined Work and reverse engineering for debugging such modifications, if you also do each of the following:<br><br>"
                "a) Give prominent notice with each copy of the Combined Work that the Library is used in it and that the Library and its use are covered by this License.<br>"
                "b) Accompany the Combined Work with a copy of the GNU GPL and this license document.<br>"
                "c) For a Combined Work that displays copyright notices during execution, include the copyright notice for the Library among these notices, as well as a reference directing the user to the copies of the GNU GPL and this license document.<br>"
                "d) Do one of the following:<br>"
                "0) Convey the Minimal Corresponding Source under the terms of this License, and the Corresponding Application Code in a form suitable for, and under terms that permit, the user to recombine or relink the Application with a modified version of the Linked Version to produce a modified Combined Work, in the manner specified by section 6 of the GNU GPL for conveying Corresponding Source.<br>"
                "1) Use a suitable shared library mechanism for linking with the Library. A suitable mechanism is one that (a) uses at run time a copy of the Library already present on the user's computer system, and (b) will operate properly with a modified version of the Library that is interface-compatible with the Linked Version.<br>"
                "e) Provide Installation Information, but only if you would otherwise be required to provide such information under section 6 of the GNU GPL, and only to the extent that such information is necessary to install and execute a modified version of the Combined Work produced by recombining or relinking the Application with a modified version of the Linked Version. (If you use option 4d0, the Installation Information must accompany the Minimal Corresponding Source and Corresponding Application Code. If you use option 4d1, you must provide the Installation Information in the manner specified by section 6 of the GNU GPL for conveying Corresponding Source.)<br><br>"
                "5. Combined Libraries.<br>"
                "You may place library facilities that are a work based on the Library side by side in a single library together with other library facilities that are not Applications and are not covered by this License, and convey such a combined library under terms of your choice, if you do both of the following:<br><br>"
                "a) Accompany the combined library with a copy of the same work based on the Library, uncombined with any other library facilities, conveyed under the terms of this License.<br>"
                "b) Give prominent notice with the combined library that part of it is a work based on the Library, and explaining where to find the accompanying uncombined form of the same work.<br><br>"
                "6. Revised Versions of the GNU Lesser General Public License.<br>"
                "The Free Software Foundation may publish revised and/or new versions of the GNU Lesser General Public License from time to time. Such new versions will be similar in spirit to the present version, but may differ in detail to address new problems or concerns.<br>"
                "Each version is given a distinguishing version number. If the Library as you received it specifies that a certain numbered version of the GNU Lesser General Public License “or any later version” applies to it, you have the option of following the terms and conditions either of that published version or of any later version published by the Free Software Foundation. If the Library as you received it does not specify a version number of the GNU Lesser General Public License, you may choose any version of the GNU Lesser General Public License ever published by the Free Software Foundation.<br>"
                "If the Library as you received it specifies that a proxy can decide whether future versions of the GNU Lesser General Public License shall apply, that proxy's public statement of acceptance of any version is permanent authorization for you to choose that version for the Library.<br><br><br>"
                "<b style=color:"+ colorOrange +";>MIT LICENSE</b><br>"
                "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:<br><br>"
                "The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.<br><br>"
                "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.<br><br><br>"
                "<b style=color:"+ colorOrange +";>CREATIVE COMMONS ATTRIBUTION 4.0 INTERNATIONAL PUBLIC LICENSE</b><br>"
                "By exercising the Licensed Rights (defined below), You accept and agree to be bound by the terms and conditions of this Creative Commons Attribution 4.0 International Public License (\"Public License\"). To the extent this Public License may be interpreted as a contract, You are granted the Licensed Rights in consideration of Your acceptance of these terms and conditions, and the Licensor grants You such rights in consideration of benefits the Licensor receives from making the Licensed Material available under these terms and conditions.<br><br>"
                "Section 1 – Definitions.<br>"
                "a. Adapted Material means material subject to Copyright and Similar Rights that is derived from or based upon the Licensed Material and in which the Licensed Material is translated, altered, arranged, transformed, or otherwise modified in a manner requiring permission under the Copyright and Similar Rights held by the Licensor. For purposes of this Public License, where the Licensed Material is a musical work, performance, or sound recording, Adapted Material is always produced where the Licensed Material is synched in timed relation with a moving image.<br>"
                "b. Adapter's License means the license You apply to Your Copyright and Similar Rights in Your contributions to Adapted Material in accordance with the terms and conditions of this Public License.<br>"
                "c. Copyright and Similar Rights means copyright and/or similar rights closely related to copyright including, without limitation, performance, broadcast, sound recording, and Sui Generis Database Rights, without regard to how the rights are labeled or categorized. For purposes of this Public License, the rights specified in Section 2(b)(1)-(2) are not Copyright and Similar Rights.<br>"
                "d. Effective Technological Measures means those measures that, in the absence of proper authority, may not be circumvented under laws fulfilling obligations under Article 11 of the WIPO Copyright Treaty adopted on December 20, 1996, and/or similar international agreements.<br>"
                "e. Exceptions and Limitations means fair use, fair dealing, and/or any other exception or limitation to Copyright and Similar Rights that applies to Your use of the Licensed Material.<br>"
                "f. Licensed Material means the artistic or literary work, database, or other material to which the Licensor applied this Public License.<br>"
                "g. Licensed Rights means the rights granted to You subject to the terms and conditions of this Public License, which are limited to all Copyright and Similar Rights that apply to Your use of the Licensed Material and that the Licensor has authority to license.<br>"
                "h. Licensor means the individual(s) or entity(ies) granting rights under this Public License.<br>"
                "i. Share means to provide material to the public by any means or process that requires permission under the Licensed Rights, such as reproduction, public display, public performance, distribution, dissemination, communication, or importation, and to make material available to the public including in ways that members of the public may access the material from a place and at a time individually chosen by them.<br>"
                "j. Sui Generis Database Rights means rights other than copyright resulting from Directive 96/9/EC of the European Parliament and of the Council of 11 March 1996 on the legal protection of databases, as amended and/or succeeded, as well as other essentially equivalent rights anywhere in the world.<br>"
                "k. You means the individual or entity exercising the Licensed Rights under this Public License. Your has a corresponding meaning.<br><br>"
                "Section 2 – Scope.<br>"
                "a. License grant.<br>"
                "1. Subject to the terms and conditions of this Public License, the Licensor hereby grants You a worldwide, royalty-free, non-sublicensable, non-exclusive, irrevocable license to exercise the Licensed Rights in the Licensed Material to:<br>"
                "A. reproduce and Share the Licensed Material, in whole or in part; and<br>"
                "B. produce, reproduce, and Share Adapted Material.<br>"
                "2. Exceptions and Limitations. For the avoidance of doubt, where Exceptions and Limitations apply to Your use, this Public License does not apply, and You do not need to comply with its terms and conditions.<br>"
                "3. Term. The term of this Public License is specified in Section 6(a).<br>"
                "4. Media and formats; technical modifications allowed. The Licensor authorizes You to exercise the Licensed Rights in all media and formats whether now known or hereafter created, and to make technical modifications necessary to do so. The Licensor waives and/or agrees not to assert any right or authority to forbid You from making technical modifications necessary to exercise the Licensed Rights, including technical modifications necessary to circumvent Effective Technological Measures. For purposes of this Public License, simply making modifications authorized by this Section 2(a)(4) never produces Adapted Material.<br>"
                "5. Downstream recipients.<br>"
                "A. Offer from the Licensor – Licensed Material. Every recipient of the Licensed Material automatically receives an offer from the Licensor to exercise the Licensed Rights under the terms and conditions of this Public License.<br>"
                "B. No downstream restrictions. You may not offer or impose any additional or different terms or conditions on, or apply any Effective Technological Measures to, the Licensed Material if doing so restricts exercise of the Licensed Rights by any recipient of the Licensed Material.<br>"
                "6. No endorsement. Nothing in this Public License constitutes or may be construed as permission to assert or imply that You are, or that Your use of the Licensed Material is, connected with, or sponsored, endorsed, or granted official status by, the Licensor or others designated to receive attribution as provided in Section 3(a)(1)(A)(i).<br>"
                "b. Other rights.<br>"
                "1. Moral rights, such as the right of integrity, are not licensed under this Public License, nor are publicity, privacy, and/or other similar personality rights; however, to the extent possible, the Licensor waives and/or agrees not to assert any such rights held by the Licensor to the limited extent necessary to allow You to exercise the Licensed Rights, but not otherwise.<br>"
                "2. Patent and trademark rights are not licensed under this Public License.<br>"
                "3. To the extent possible, the Licensor waives any right to collect royalties from You for the exercise of the Licensed Rights, whether directly or through a collecting society under any voluntary or waivable statutory or compulsory licensing scheme. In all other cases the Licensor expressly reserves any right to collect such royalties.<br><br>"
                "Section 3 – License Conditions.<br>"
                "Your exercise of the Licensed Rights is expressly made subject to the following conditions.<br>"
                "a. Attribution.<br>"
                "1. If You Share the Licensed Material (including in modified form), You must:<br>"
                "A. retain the following if it is supplied by the Licensor with the Licensed Material:<br>"
                "i. identification of the creator(s) of the Licensed Material and any others designated to receive attribution, in any reasonable manner requested by the Licensor (including by pseudonym if designated);<br>"
                "ii. a copyright notice;<br>"
                "iii. a notice that refers to this Public License;<br>"
                "iv. a notice that refers to the disclaimer of warranties;<br>"
                "v. a URI or hyperlink to the Licensed Material to the extent reasonably practicable;<br>"
                "B. indicate if You modified the Licensed Material and retain an indication of any previous modifications; and<br>"
                "C. indicate the Licensed Material is licensed under this Public License, and include the text of, or the URI or hyperlink to, this Public License.<br>"
                "2. You may satisfy the conditions in Section 3(a)(1) in any reasonable manner based on the medium, means, and context in which You Share the Licensed Material. For example, it may be reasonable to satisfy the conditions by providing a URI or hyperlink to a resource that includes the required information.<br>"
                "3. If requested by the Licensor, You must remove any of the information required by Section 3(a)(1)(A) to the extent reasonably practicable.<br>"
                "4. If You Share Adapted Material You produce, the Adapter's License You apply must not prevent recipients of the Adapted Material from complying with this Public License.<br><br>"
                "Section 4 – Sui Generis Database Rights.<br>"
                "Where the Licensed Rights include Sui Generis Database Rights that apply to Your use of the Licensed Material:<br>"
                "a. for the avoidance of doubt, Section 2(a)(1) grants You the right to extract, reuse, reproduce, and Share all or a substantial portion of the contents of the database;<br>"
                "b. if You include all or a substantial portion of the database contents in a database in which You have Sui Generis Database Rights, then the database in which You have Sui Generis Database Rights (but not its individual contents) is Adapted Material; and<br>"
                "c. You must comply with the conditions in Section 3(a) if You Share all or a substantial portion of the contents of the database.<br>"
                "For the avoidance of doubt, this Section 4 supplements and does not replace Your obligations under this Public License where the Licensed Rights include other Copyright and Similar Rights.<br><br>"
                "Section 5 – Disclaimer of Warranties and Limitation of Liability.<br>"
                "a. Unless otherwise separately undertaken by the Licensor, to the extent possible, the Licensor offers the Licensed Material as-is and as-available, and makes no representations or warranties of any kind concerning the Licensed Material, whether express, implied, statutory, or other. This includes, without limitation, warranties of title, merchantability, fitness for a particular purpose, non-infringement, absence of latent or other defects, accuracy, or the presence or absence of errors, whether or not known or discoverable. Where disclaimers of warranties are not allowed in full or in part, this disclaimer may not apply to You.<br>"
                "b. To the extent possible, in no event will the Licensor be liable to You on any legal theory (including, without limitation, negligence) or otherwise for any direct, special, indirect, incidental, consequential, punitive, exemplary, or other losses, costs, expenses, or damages arising out of this Public License or use of the Licensed Material, even if the Licensor has been advised of the possibility of such losses, costs, expenses, or damages. Where a limitation of liability is not allowed in full or in part, this limitation may not apply to You.<br>"
                "c. The disclaimer of warranties and limitation of liability provided above shall be interpreted in a manner that, to the extent possible, most closely approximates an absolute disclaimer and waiver of all liability.<br><br>"
                "Section 6 – Term and Termination.<br>"
                "a. This Public License applies for the term of the Copyright and Similar Rights licensed here. However, if You fail to comply with this Public License, then Your rights under this Public License terminate automatically.<br>"
                "b. Where Your right to use the Licensed Material has terminated under Section 6(a), it reinstates:<br>"
                "1. automatically as of the date the violation is cured, provided it is cured within 30 days of Your discovery of the violation; or<br>"
                "2. upon express reinstatement by the Licensor.<br>"
                "For the avoidance of doubt, this Section 6(b) does not affect any right the Licensor may have to seek remedies for Your violations of this Public License.<br>"
                "c. For the avoidance of doubt, the Licensor may also offer the Licensed Material under separate terms or conditions or stop distributing the Licensed Material at any time; however, doing so will not terminate this Public License.<br>"
                "d. Sections 1, 5, 6, 7, and 8 survive termination of this Public License.<br><br>"
                "Section 7 – Other Terms and Conditions.<br>"
                "a. The Licensor shall not be bound by any additional or different terms or conditions communicated by You unless expressly agreed.<br>"
                "b. Any arrangements, understandings, or agreements regarding the Licensed Material not stated herein are separate from and independent of the terms and conditions of this Public License.<br><br>"
                "Section 8 – Interpretation.<br>"
                "a. For the avoidance of doubt, this Public License does not, and shall not be interpreted to, reduce, limit, restrict, or impose conditions on any use of the Licensed Material that could lawfully be made without permission under this Public License.<br>"
                "b. To the extent possible, if any provision of this Public License is deemed unenforceable, it shall be automatically reformed to the minimum extent necessary to make it enforceable. If the provision cannot be reformed, it shall be severed from this Public License without affecting the enforceability of the remaining terms and conditions.<br>"
                "c. No term or condition of this Public License will be waived and no failure to comply consented to unless expressly agreed to by the Licensor.<br>"
                "d. Nothing in this Public License constitutes or may be interpreted as a limitation upon, or waiver of, any privileges and immunities that apply to the Licensor or You, including from the legal processes of any jurisdiction or authority.<br>"
                );
    ui->txt_output->setCursorWidth(0);
    ui->txt_output_neg->setCursorWidth(0);
    ui->txt_output_neg->hide();
    ui->progressBar->hide();
    ui->txt_searchfield->setFocus();
    ui->lbl_status->clear();
    ui->lbl_error->clear();

    //workaround to show placeholder text
    ui->txt_searchfield->insertPlainText(" ");
    QTextCursor cursor = ui->txt_searchfield->textCursor();
    cursor.deletePreviousChar();

    QPalette p = ui->txt_searchfield->palette();
    p.setColor(QPalette::PlaceholderText, QColor(120,120,120,255));
    ui->txt_searchfield->setPalette(p);

    keyCtrlReturn = new QShortcut(this);
    keyCtrlReturn->setKey(Qt::CTRL | Qt::Key_Return);
    connect(keyCtrlReturn, SIGNAL(activated()), this, SLOT(slot_shortcutCtrlReturn()));

    torPublished = "";
    torDataVec = fetch_tor_data();
    torPublished.chop(3);
    if(torPublished.length() > 0){
        ui->lbl_status->setText("TOR-Data from: " + torPublished + " UTC ");
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_btn_about_clicked()
{
    if(ui->stackedWidget->currentIndex() == 0){
        ui->stackedWidget->setCurrentIndex(1);
        ui->btn_search->setVisible(false);
        ui->btn_about->setText("X");
    } else {
        ui->stackedWidget->setCurrentIndex(0);
        ui->btn_search->setVisible(true);
        ui->btn_about->setText("?");
    }
}


void Widget::on_btn_refreshTOR_clicked()
{
    download_tor_json();
    fetch_tor_data();
    torPublished.chop(3);
    if(torPublished.length() > 0){
        ui->lbl_status->setText("TOR-Data from: " + torPublished + " UTC ");
    }
    else {
        ui->lbl_error->setText("| No TOR-Data!");
    }
}


void Widget::on_btn_search_clicked()
{
    inputSet.clear();

    if(!mmdb_check()) return;

    QStringList inputStrList = ui->txt_searchfield->toPlainText().split("\n");

    foreach(const auto &item, inputStrList){
        inputSet.insert(item.trimmed());
    }

    int inputSize = inputSet.size();
    int counter = 0;

    ui->progressBar->setValue(0);
    ui->progressBar->show();

    //INPUT-DATA
    foreach(const auto &item, inputSet){

        //CHECK MMDB-DATA
        QProcess mmdbinspect;
        mmdbinspect.start(mmdbinspect_path, QStringList() << "--db" << asndb_path << "--db" << countrydb_path << item);
        mmdbinspect.waitForFinished();
        QByteArray outputRaw(mmdbinspect.readAllStandardOutput());
        QByteArray outputError(mmdbinspect.readAllStandardError());

        counter++;
        //qDebug() << float(counter) / float(inputSize) * 100;
        ui->progressBar->setValue(float(counter) / float(inputSize) * 100);
        if(counter == inputSize){
            ui->progressBar->hide();
        }

        if(outputError.length() > 0){
            if(item.isEmpty()) {
                continue;
            }
            else {
                if(outputError.contains("not a valid IP")){
                    if(ui->txt_output_neg->document()->isEmpty()){
                        ui->txt_output_neg->setPlainText("not a valid IP address:");
                    }
                    ui->txt_output_neg->show();
                    ui->txt_output_neg->appendPlainText(item);
                }
            }
            continue;
        }

        QJsonDocument json_doc = QJsonDocument::fromJson(outputRaw);
        QJsonArray json_root = json_doc.array();

        if(ui->txt_output->document()->isEmpty()){
            ui->txt_output->setText("<span style='white-space: pre-wrap;'><font color='grey'>"
                                    + truncate("ASN", padASN, ' ', true)
                                    + divider + truncate("ISO", padISO, ' ', true)
                                    + divider + truncate("COUNTRY", padCOUNTRY, ' ', true)
                                    + divider + truncate("URLhaus", padURLHAUS, ' ', true)
                                    + divider + truncate("ThreatFox", padTHREATFOX, ' ', true)
                                    + divider + truncate("TOR", padTOR, ' ', true)
                                    + divider + "IP"
                                    + "</font>");
        }

        QJsonObject json_asn_obj = json_root.at(0).toObject();
        QJsonObject json_country_obj = json_root.at(1).toObject();

        QString asn = json_asn_obj
                .value("Records")
                .toArray().at(0)
                .toObject().value("Record")
                .toObject().value("autonomous_system_organization").toString();

        QString iso = json_country_obj
                .value("Records")
                .toArray().at(0)
                .toObject().value("Record")
                .toObject().value("country")
                .toObject().value("iso_code").toString();

        QString country = json_country_obj
                .value("Records")
                .toArray().at(0)
                .toObject().value("Record")
                .toObject().value("country")
                .toObject().value("names")
                .toObject().value("en").toString();


        //CHECK URLHAUS
        QString urlhaus = fetch_urlhaus(item.toUtf8());

        //CHECK THREATFOX
        QString threatfox = fetch_threatfox(item.toUtf8());

        //CHECK TOR-DATA
        QString tor;
        if(torDataVec.size() == 0){
            tor = "<font color=grey>"+ truncate("no data", padTOR, ' ', true) +"</font>";
        }
        else {
            foreach(const auto &element, torDataVec){
                if(element.contains(item)){
                    QStringList firstElem = element.split('|');
                    tor = "<font color="+ colorPurple +">" + truncate(firstElem.first(), padTOR, ' ', true) + "</font>";
                    break;
                } else {
                    tor = "<font color=grey>"+ truncate("-", padTOR, ' ', true) +"</font>";
                }
            }
        }


        if(asn.isEmpty()) { asn = "<font color=grey>" + truncate("-", padASN, ' ', true) + "</font>"; }
        else { asn = "<font color="+ colorGreen +">" + truncate(asn, padASN, ' ', true) + "</font>"; }

        if(iso.isEmpty()) { iso = "<font color=grey>" + truncate("-", padISO, ' ', true) + "</font>"; }
        else { iso = truncate(iso, padISO, ' ', true); }

        if(country.isEmpty()) { country = "<font color=grey>" + truncate("-", padCOUNTRY, ' ', true) + "</font>"; }
        else { country = truncate(country, padCOUNTRY, ' ', true); }

        ui->txt_output->append("<span style='white-space: pre-wrap;'>" + asn
                               + divider + iso
                               + divider + country
                               + divider + urlhaus
                               + divider + threatfox
                               + divider + tor
                               + divider + item
                               );
    }
}


void Widget::slot_shortcutCtrlReturn()
{
    on_btn_search_clicked();
}


void Widget::slot_finished_tordownload()
{

}


QString Widget::truncate(QString input, int width, QChar fillchar, bool trunc)
{
    if(input.length() > width){
        return input.leftJustified(width -1, fillchar, trunc) + "…";
    }
    else return input.leftJustified(width, fillchar, trunc);
}


bool Widget::mmdb_check()
{
    ui->lbl_error->clear();
    QDir mmdbDir(QDir::currentPath() + "/mmdb");
    if(!mmdbDir.exists()){
        ui->lbl_error->setText(" | directory 'mmdb' does not exist!");
        return false;
    }

    QStringList asnFilter;
    asnFilter << "*asn*.mmdb";

    QStringList countryFilter;
    countryFilter << "*country*.mmdb";

    QStringList asnList = mmdbDir.entryList(asnFilter);
    QStringList countryList = mmdbDir.entryList(countryFilter);

    QString missing;


    if(QFile::exists(mmdbDir.absoluteFilePath("mmdbinspect.exe"))){
        mmdbinspect_path = mmdbDir.absoluteFilePath("mmdbinspect.exe");
    } else {
        missing += " | 'mmdbinspect.exe' missing!";
    }
    if(asnList.length() > 0){
        asndb_path = mmdbDir.absoluteFilePath(asnList.at(asnList.length()-1));
    } else {
        missing += " | 'asn.mmdb' file missing!";
    }
    if(countryList.length() > 0){
        countrydb_path = mmdbDir.absoluteFilePath(countryList.at(countryList.length()-1));
    } else {
        missing += " | 'country.mmdb' file missing!";
    }
    if(missing.length() > 0) {
        ui->lbl_error->setText(missing);
        return false;
    } else return true;
}

QString Widget::fetch_urlhaus(QByteArray host)
{
    QString output;

    QNetworkAccessManager netmanager;
    const QUrl url("https://urlhaus-api.abuse.ch/v1/host/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "IP-Lookup-GUI");
    QByteArray data = "host=" + host;

    QNetworkReply *reply = netmanager.post(request, data);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray urlhausData = reply->readAll();

    if(urlhausData.length() > 0){

        QJsonDocument json_doc = QJsonDocument::fromJson(urlhausData);
        QJsonObject json_root = json_doc.object();
        QSet<QString> tagsSet;

        if(json_root.value("query_status") == "ok"){
            QJsonArray urlsArr = json_root.value("urls").toArray();

            foreach(const auto &item, urlsArr){
                QJsonArray tagsArr = item.toObject().value("tags").toArray();

                foreach(const auto &item, tagsArr){
                    tagsSet.insert(item.toString());
                }
            }

            if(tagsSet.size() > 0) {
                foreach(const auto &item, tagsSet){
                    output.append(item + " ");
                }
            }
            else {output = "malware download";}

            return output = "<font color="+ colorOrange +">" + truncate(output.trimmed(), padURLHAUS, ' ', true) + "</font>";

        }
        else {
            return output = "<font color=grey>" + truncate("-", padURLHAUS, ' ', true) + "</font>";
        }

    }
    else {return output = "<font color=grey>"+ truncate("offline", padURLHAUS, ' ', true) +"</font>";}

    return output.trimmed();
}

QString Widget::fetch_threatfox(QByteArray search)
{
    QString output;

    QNetworkAccessManager netmanager;
    const QUrl url("https://threatfox-api.abuse.ch/api/v1/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "IP-Lookup-GUI");

    QByteArray data = "{ \"query\": \"search_ioc\", \"search_term\": \"" + search + "\"}";

    QNetworkReply *reply = netmanager.post(request, data);

    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray threatfoxData = reply->readAll();

    if(threatfoxData.length() > 0){

        QJsonDocument json_doc = QJsonDocument::fromJson(threatfoxData);
        QJsonObject json_root = json_doc.object();

        if(json_root.value("query_status") == "ok"){

            QJsonArray dataArr = json_root.value("data").toArray();
            QSet<QString> dataSet;
            foreach(const auto &item, dataArr){
                dataSet.insert(item.toObject().value("malware_printable").toString());
            }

            if(dataSet.size() > 0){
                foreach(const auto &item, dataSet){
                    output.append(item + " ");
                }
            }
            else {
                output = "malware found";
            }

            return output = "<font color="+ colorRed +">" + truncate(output.trimmed(), padTHREATFOX, ' ', true) + "</font>";

        }
        else {
            return output = "<font color=grey>" + truncate("-", padTHREATFOX, ' ', true) + "</font>";
        }
    }
    else {
        return output = "<font color=grey>" + truncate("offline", padTHREATFOX, ' ', true) + "</font>";
    }

    return output.trimmed();
}


QByteArray Widget::download_tor_json()
{
    ui->lbl_error->clear();
    ui->lbl_status->setText("trying to download TOR-Data... ");

    const QString url = "https://onionoo.torproject.org/details";

    QNetworkAccessManager netmanager;
    QNetworkReply *response = netmanager.get(QNetworkRequest(QUrl(url)));

    QEventLoop loop;
    connect(response, SIGNAL(finished()), this, SLOT(slot_finished_tordownload()));
    connect(response, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();

    QByteArray torData = response->readAll();

    if(response->error()){
        ui->lbl_error->setText(" | Couldn’t download TOR-Data!");
        return torData;
    } else {
        QDir mmdbDir(QDir::currentPath() + "/mmdb");
        if(!mmdbDir.exists()){
            ui->lbl_error->setText(" | directory 'mmdb' does not exist!");
            return torData;
        }
        QFile file(mmdbDir.absoluteFilePath("TOR.json"));
        file.remove();
        if(file.open(QIODevice::ReadWrite)){
            QTextStream stream(&file);
            stream << torData;
        }
        file.close();
        torDataVec = fetch_tor_data();
        return torData;
    }
}


QVector<QString> Widget::fetch_tor_data()
{
    QVector<QString> torEntries;
    QByteArray torData;

    QDir mmdbDir(QDir::currentPath() + "/mmdb");
    if(!mmdbDir.exists()){
        ui->lbl_error->setText(" | directory 'mmdb' does not exist!");
        return torEntries;
    }

    QFile file(mmdbDir.absoluteFilePath("TOR.json"));
    if(file.open(QIODevice::ReadOnly)){
        torData = file.readAll();
    } else {
        torData = download_tor_json();
    }
    file.close();


    if(torData.length() == 0) {
        ui->lbl_error->setText(" | No TOR-Data!");
        return torEntries;
    }

    if(!mmdb_check()) return torEntries;


    QJsonDocument json_doc = QJsonDocument::fromJson(torData);
    QJsonObject json_root = json_doc.object();

    torPublished = json_root.value("relays_published").toString();

    QJsonArray relays = json_root.value("relays").toArray();
    if(relays.size() == 0){
        ui->lbl_error->setText(" | Corrupt TOR-Data!");
        return torEntries;
    }

    static const QRegularExpression re("(?:.(?!:))+$");

    for(int i = 0; i < relays.count(); i++){

        QString firstSeen = relays.at(i).toObject().value("first_seen").toString();
        QJsonArray orAddresses = relays.at(i).toObject().value("or_addresses").toArray();
        QSet<QString> torAddresses;

        for(int j = 0; j < orAddresses.count(); j++){
            QString tmp = orAddresses.at(j).toString();
            tmp.remove("[").remove(re).remove("]");
            torAddresses.insert(tmp);
        }

        QString serverType;
        QJsonArray exitAddresses = relays.at(i).toObject().value("exit_addresses").toArray();

        if(exitAddresses.empty()) { serverType = "TOR-RELAY"; }
        else {
            serverType = "TOR-EXIT";
            for(int j = 0; j < exitAddresses.count(); j++){
                torAddresses.insert(exitAddresses.at(j).toString());
            }
        }

        QString IPs;
        foreach(const auto &item, torAddresses){
            IPs.append(item + " ");
        }

        torEntries.push_back(serverType + "|" + firstSeen + "%" + IPs.trimmed());
    }

    return torEntries;
}


